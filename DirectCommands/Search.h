#include "Aria.h"
#include "iostream"

class Search
{
	private:
		ArRobot *myRobot;
		ArSonarDevice *mySonar;
		int width;
		int stopDistance;
		int timeSet;
	public:
		Search(ArRobot *robot, ArSonarDevice *sonar);
		int seek(int lastPositionXY[2], int currentPositionXY[2]);
};
