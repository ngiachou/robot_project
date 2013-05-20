#include "Aria.h"
#include "ServerSocket.h"
#include "SocketException.h"

class Follow : public ArAction{
    public:
        //Constructor
        Follow(ServerSocket *socket, double speed);

        //called by action resolver
        ArActionDesired *fire(ArActionDesired currentDesired);
    protected:
        /* Our current desired action: fire() modifies this object and returns
        to the action resolver a pointer to this object.
        This object is kept as a class member so that it persists after fire()
        returns (otherwise fire() would have to create a new object each invocation,
        but would never be able to delete that object).
        */
        ArActionDesired myDesired;

        //Socket for communication with tld
        ServerSocket *mySocket;

        double mySpeed;
};
