#include "Movement.h"
Movement::Movement(ArRobot *robot)
{
	myRobot = robot;
}

void Movement::forward(int velocity)
{
	myRobot->lock();
	myRobot->setRotVel(0);
	myRobot->setVel(velocity);
	myRobot->unlock();
}

void Movement::turn(float rotVelocity)
{
	myRobot->lock();
	myRobot->setVel(0);
	myRobot->setRotVel(rotVelocity);
	myRobot->unlock();
}

void Movement::stop()
{
	myRobot->lock();
        myRobot->stop();
        myRobot->unlock();
}
