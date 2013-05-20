#include "Aria.h"

class Movement
{
	private:
		ArRobot *myRobot;
	public:
		Movement(ArRobot *robot);
		void forward(int velocity);
		void turn(float rotVelocity);
		void stop();
};
