#include "GoTo.h"

GoTo::GoTo(ArRobot *robot, ArPathPlanningTask *pathTask, ArMap *map){

	//Mallon 8elw map kai robot gia to localization
	myRobot = robot;

	myMap = map;

	//An dn exw xarti termatizw
	if(myMap->getFileName() == NULL || strlen(myMap->getFileName()) == 0){
		ArLog::log(ArLog::Normal,"No map");
		Aria::exit(1);
	}

	//path task
	myPathTask = pathTask;

}

//The main method
int GoTo::run(int currentBBCenter[2]){
	//Reached target location give the flow to Follow
	if(myPathTask->getState() == ArPathPlanningTask::REACHED_GOAL)
		return 1;

	//Not moving towards goal then get one
	if(myPathTask->getState() != ArPathPlanningTask::MOVING_TO_GOAL){
		//This call is to get the x,y from mapping
		getGoal();

		myRobot->clearDirectMotion();
		//Plan to pose
		myPathTask->pathPlanToGoal("across");
		//Flow stays in GoTo
		return 3;
	}
	if(myPathTask->getState() == ArPathPlanningTask::FAILED_PLAN)
		return 2;
	//Moving to goal keep flow until goal reached
	else{
		return 3;
	}

}

//modifies the myGoal var
int GoTo::getGoal(){
	//TODO make the maping for estimating targets position
	ArPose curPose;

	curPose = myRobot->getPose();

//	std::cout << "x: " << curPose.getX() << " ,y: " << curPose.getY() << std::endl;
	myGoal.setPose(2,38);

	return 1;
}
