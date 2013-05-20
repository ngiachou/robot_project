all: robotServer

CFLAGS=-fPIC -Wall -g
ARIA_INCLUDE=-I/usr/local/Arnl/include/Aria -I/usr/local/Arnl/include/ArNetworking -I/usr/local/Arnl/include
ARIA_LINK=-L/usr/local/Arnl/lib -lBaseArnl -lArNetworkingForArnl -lAriaForArnl -lSonArnl -lpthread -ldl -lrt -Xlinker -Bstatic -lstdc++ -Xlinker -Bdynamic -lpthread -ldl -lrt

robotServer: Socket.o ServerSocket.o Movement.o Follow.o GoTo.o Search.o
	$(CXX) $(CFLAGS) $(ARIA_INCLUDE) directRobotServer.cpp Search.o GoTo.o Movement.o Follow.o Socket.o ServerSocket.o -o robotServer $(ARIA_LINK)

Movement.o:
	$(CXX) $(CFLAGS) $(ARIA_INCLUDE) -c Movement.cpp -o Movement.o $(ARIA_LINK)

Follow.o:
	$(CXX) $(CFLAGS) $(ARIA_INCLUDE) -c Follow.cpp -o Follow.o $(ARIA_LINK)

GoTo.o:
	$(CXX) $(CFLAGS) $(ARIA_INCLUDE) -c GoTo.cpp -o GoTo.o $(ARIA_LINK)

Search.o:
	$(CXX) $(CFLAGS) $(ARIA_INCLUDE) -c Search.cpp -o Search.o $(ARIA_LINK)



clean:
	rm -f *.o
	rm robotServer

