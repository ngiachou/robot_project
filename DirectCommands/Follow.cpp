#include "Follow.h"
#include "Movement.h"
#include<stdio.h>
Follow::Follow(ArRobot *robot,ArSonarDevice *sonar)
{
	myRobot = robot;
	mySonar = sonar;
	maxRotVel = 36;
}

int Follow::run(int centerOfBB[2])
{
	double range = mySonar->currentReadingPolar(-70, 70) - myRobot->getRobotRadius();
	Movement move  = Movement(myRobot);


	//if we have a target
        if(centerOfBB[0] != -1)
        {
                //target in the middle
                if(WIDTH/3 <= centerOfBB[0] && centerOfBB[0] <= 2*WIDTH/3 && range > STOPDISTANCE)
                {                move.forward(250);
                		printf("forward\n");
		}//target is not in the middle
                if(centerOfBB[0] < WIDTH/3 || centerOfBB[0] > 2*WIDTH/3)
                {
                        float rotVelW = (2*centerOfBB[0] - WIDTH) / WIDTH; //mapping ths theshs X se times [-1 1] analoga me th thesh sto frame
                        move.turn(-rotVelW*maxRotVel);
			printf("turn r=%f, 2*x=%d,-w=%d \n",rotVelW,2*centerOfBB[0],WIDTH);
                }
                if(range < STOPDISTANCE)
                        return 3;

                return 1;

        }
        //We have no target
        else{
                move.stop();
                return 2;
        }

}
