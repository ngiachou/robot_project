#include "Aria.h"
#include "follow.h"
#include "ServerSocket.h"
#include "SocketException.h"



int main(int argc, char** argv){
	// Create the socket
	ServerSocket server ( 30000 );
	Aria::init();
	ArRobot robot;
	//Sonar device
	ArSonarDevice sonar;

	ArArgumentParser parser(&argc, argv);
	parser.loadDefaultArguments();

	ServerSocket socket;
	server.accept ( socket );

	//Create our follow action
	Follow follow(&socket, 500);

	// Robot motion limiter actions (if obstacles are detected by sonar)
	ArActionLimiterForwards limiter("speed limiter near", 350, 800, 200);
	ArActionLimiterForwards limiterFar("speed limiter far", 400, 1250, 300);
	ArActionLimiterBackwards backwardsLimiter;
	ArActionConstantVelocity stop("stop", 0);

	//Add the sonar to the robot
	robot.addRangeDevice(&sonar);

	// Connect to the robot, get some initial data from it such as type and name,
	// and then load parameter files for this robot.
  	ArRobotConnector robotConnector(&parser, &robot);

  	if(!robotConnector.connectRobot()){
		ArLog::log(ArLog::Terse, "Robot Server: Could not connect to the robot.");
		if(parser.checkHelpAndWarnUnparsed()){
			// -help not given
			Aria::logOptions();
			Aria::exit(1);
		}
	}
	if (!Aria::parseArgs()){
		Aria::logOptions();
		Aria::shutdown();
		return 1;
	}

	ArLog::log(ArLog::Normal, "Robot Server: Connected.");

	// Add our actions in order. The second argument is the priority,
	// with higher priority actions going first, and possibly pre-empting lower
	// priority actions.
	robot.addAction(&follow,10);
	robot.addAction(&limiter, 7);
	robot.addAction(&limiterFar, 6);
	robot.addAction(&backwardsLimiter, 5);
	robot.addAction(&stop, 3);

	// Enable the motors, disable amigobot sounds
	robot.enableMotors();

	// Run the robot processing cycle.
	// 'true' means to return if it loses connection,
	// after which we exit the program.
	robot.run(true);

	Aria::shutdown();
	return 0;
}
