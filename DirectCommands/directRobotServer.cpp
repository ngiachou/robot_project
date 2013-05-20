#include "Aria.h"
#include "ArNetworking.h"
#include "Arnl.h"
#include "ArSonarLocalizationTask.h"
#include "ServerSocket.h"
#include "SocketException.h"
#include <string>
#include <iostream>
#include "Follow.h"
#include "GoTo.h"
#include "Search.h"


using namespace std;

#define WIDTH 640
#define HEIGHT 480
#define STOP_DISTANCE 500

int main ( int argc, char *argv[] ){
//cout << "running....\n";
try{
	// Create the socket
	ServerSocket server ( 30000 );

	Aria::init();
	Arnl::init();

	ArRobot robot;
	ArArgumentParser parser(&argc, argv);
	parser.loadDefaultArguments();
	ArSonarDevice sonar;
	ArSimpleConnector simpleConnector(&parser);

	// Our server for mobile eyes
	ArServerBase moServer;

	// Set up our simpleOpener
	ArServerSimpleOpener simpleOpener(&parser);

	parser.loadDefaultArguments();
  	if (!Aria::parseArgs () || !parser.checkHelpAndWarnUnparsed()){
    		Aria::logOptions ();
   		Aria::exit (1);
  	}

	//Add the sonar to the robot
	robot.addRangeDevice(&sonar);

  	// Look for map in the current directory
  	ArMap arMap;
  	// set it up to ignore empty file names (otherwise the parseFile
  	// on the config will fail)
  	arMap.setIgnoreEmptyFileName (true);

	// First open the server 
	if (!simpleOpener.open(&moServer)){
		if (simpleOpener.wasUserFileBad())
    			ArLog::log(ArLog::Normal, "Bad user file");
		else
    			ArLog::log(ArLog::Normal, "Could not open server port");
  		exit(2);
	}

        // Connect to the robot
        if (!simpleConnector.connectRobot (&robot)){
                ArLog::log (ArLog::Normal, "Could not connect to robot... exiting");
                Aria::exit (3);
        }

	// Create the localization task (it will start its own thread here)
	ArSonarLocalizationTask locTask(&robot, &sonar, &arMap);

	ArLocalizationManager locManager(&robot, &arMap);

	ArLog::log(ArLog::Normal, "Creating sonar localization task");
	locManager.addLocalizationTask(&locTask);




	// Set the initial pose to the robot's "Home" position from the map, or
	// (0,0,0) if none, then let the localization thread take over.
	locTask.localizeRobotAtHomeNonBlocking();

	//Create the path planning task
	ArPathPlanningTask pathTask(&robot,&sonar,&arMap);

	ArLog::log(ArLog::Normal, "Robot Server: Connected.");

	robot.enableMotors();
	robot.clearDirectMotion();

	// Start the robot processing cycle running in the background.
	// True parameter means that if the connection is lost, then the
	// run loop ends.
	robot.runAsync(true);

	// Read in parameter files.
  	Aria::getConfig ()->useArgumentParser (&parser);
  	if (!Aria::getConfig ()->parseFile (Arnl::getTypicalParamFileName ())){
		ArLog::log (ArLog::Normal, "Trouble loading configuration file, exiting");
		Aria::exit (5);
	}

	//Create the three states
	robot.lock();
	Follow follow = Follow(&robot,&sonar);
	GoTo goTo(&robot,&pathTask,&arMap);
	Search s(&robot,&sonar);

	// These provide various kinds of information to the client:
	ArServerInfoRobot serverInfoRobot(&moServer, &robot);
	ArServerInfoSensor serverInfoSensor(&moServer, &robot);
	ArServerInfoPath serverInfoPath(&moServer, &robot, &pathTask);
	
	// Provide the map to the client (and related controls):
	// This uses both lines and points now, since everything except
	// sonar localization uses both (path planning with sonar still uses both)
  	ArServerHandlerMap serverMap(&moServer, &arMap);
	
	// Provides localization info and allows the client (MobileEyes) to relocalize at a given
	// pose:
	ArServerInfoLocalization serverInfoLocalization(&moServer, &robot, &locTask);
	ArServerHandlerLocalization serverLocHandler(&moServer, &robot, &locTask);

	robot.unlock();

	moServer.runAsync();

	//Main loop
	while (true){
		//The socket to accept connection
		ServerSocket new_sock;
		server.accept ( new_sock );
		int state = 1;		//1 = Follow, 2 = Search, 3 = GoTo
		int lastPos[2];		//Storing last position of BB to search the target
		int data[2];		//matrix with X,Y of BB
		try{
			while ( true ){
				//receive data from tld
				new_sock >> data;
				//cout << data[0] << "," << data[1] << endl;

				if(data[0] != -1)
					lastPos[0] = data[0];

				//cout << state <<endl; //for debugging
				//Main logic
				switch(state){

					case 1:
						cout << "Following target\n";
						state = follow.run(data);
					break;
					case 2:
						cout << "Searching for target\n";
						state = s.seek(lastPos, data);
					break;
					case 3:
						cout << "Going to ...\n";
						state = goTo.run(data);
					break;
					default:
						cout << "Not a case for state\n";
					break;
				}
				std::cout << "Loc score: " << locTask.getLocalizationScore() << std::endl;
			}
		}
		catch ( SocketException& ) {
			cout << "Lost Connection" << endl;
			robot.lock();
			robot.stop();
			robot.unlock();
		}
	}
}
catch ( SocketException& e ){
	std::cout << "Exception was caught:" << e.description() << "\nExiting.\n";
}

ArLog::log(ArLog::Normal, "RobotServer: Exiting.");
return 0;
}
