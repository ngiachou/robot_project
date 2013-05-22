#include "Search.h"
#include "Movement.h"

Search::Search(ArRobot *robot, ArSonarDevice *sonar)
{
	myRobot = robot;
	mySonar = sonar;
	width = 640;
	stopDistance = 250;
	timeSet = 0;
}

int Search::seek(int lastPositionXY[2],int currentPositionXY[2])
{
	Movement move = Movement(myRobot);
	double range = mySonar->currentReadingPolar(-70, 70) - myRobot->getRobotRadius();

	ArTime start;
        //using timeSet to start the counting the first time we enter Search
        if (timeSet == 0)
                timeSet = start.getSec();

        //if searching for more thatn 1o secs switch to goTo
        if(start.getSec() - timeSet > 10)
        {	timeSet = 0;
		return 3;
	}

        //if we have found a target
        if( currentPositionXY[0] != -1 )
        {       timeSet = 0;
                std::cout << "Found target " << currentPositionXY[0] << std::endl;
                return 1;
        }

        // if we are safe
        if(range > stopDistance)
        {       //if the target was last seen on the right
                if( lastPositionXY[0] > width/2 )
                        move.turn(-36);
                //if the target was last seen on the left
                if( lastPositionXY[0] =< width/2 )
                        move.turn(36);
                return 2;
        }

	//if we are not safe
	else
	{	move.stop();
		return 3;
	}
}
