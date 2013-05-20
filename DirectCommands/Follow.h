#include "Aria.h"

class Follow
{
	private:
		ArRobot *myRobot;
		ArSonarDevice *mySonar;
		static const float WIDTH=640;
		static const int STOPDISTANCE=500;
		int maxRotVel;
	public:
		Follow(ArRobot *robot, ArSonarDevice *sonar);
		int run(int centerOfBB[2]);
};
