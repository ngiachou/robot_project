#include "Aria.h"
#include "follow.h"
#include "ServerSocket.h"
#include "SocketException.h"
#include <iostream>

#define WIDTH 640
#define HEIGHT 480

Follow::Follow(ServerSocket *socket, double speed) : ArAction("Follow"){

    mySpeed = speed;
    mySocket = socket;

}

ArActionDesired *Follow::fire(ArActionDesired currentDesired){
    //data to receive
    int data[2];
    
    //reset previous desired motion commands for safety
    myDesired.reset();

    //receive data from socket
    *mySocket >> data;
    std::cout << data[0] << "," << data[1] << std::endl;

    //if we have target
    if(data[0] != -1){
        //and we are on the right side
        if(data[0] > WIDTH/2){
    	    myDesired.setVel(0);
            myDesired.setDeltaHeading(-10);
        }
        //on the left side
        if(data[0] < WIDTH/2){
            myDesired.setVel(0);
            myDesired.setDeltaHeading(10);
        }
        //in the middle
        if(data[0] <= WIDTH/2 + 20 && data[0] >= WIDTH/2 - 20){
            myDesired.setDeltaHeading(0);
            myDesired.setVel(mySpeed);       
        }
    }
    //No target
    else{
        myDesired.setDeltaHeading(0);
        myDesired.setVel(0);
    }

    return &myDesired;
}
