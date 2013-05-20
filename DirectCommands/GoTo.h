#include"Aria.h"
#include"Arnl.h"
#include<iostream>

class GoTo{
	private:
	ArRobot *myRobot;
	ArMap *myMap;
	ArPathPlanningTask *myPathTask;
	ArPose myGoal;

	public:
	//Constructor
	GoTo(ArRobot*, ArPathPlanningTask*, ArMap*);

	//Going to goal
	int run(int[]);

	//Get the goal with mapping
	int getGoal();
};
