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

	//Don't have a plan yet
	pathPlaned = 0;

}

//The main method
int GoTo::run(int currentBBCenter[2]){

	//Don't have a plan
	if(!pathPlaned){
		//This call is to get the x,y from mapping
		getGoal();

		myRobot->clearDirectMotion();
		//Plan to pose
		myPathTask->pathPlanToGoal("across");

		//Now i have a plan
		pathPlaned = 1;

		//Flow stays in GoTo
		return 3;
	}

        //Reached target location give the flow to Follow
        if(myPathTask->getState() == ArPathPlanningTask::REACHED_GOAL){
                //Plan completed
                pathPlaned = 0;

                return 1;
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
