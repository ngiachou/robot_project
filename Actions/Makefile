all: robotServer

CFLAGS=-fPIC -Wall -g
ARIA_INCLUDE=-I/usr/local/Arnl/include/Aria -I/usr/local/Arnl/include/ArNetworking -I/usr/local/Arnl/include
ARIA_LINK=-L/usr/local/Arnl/lib -lBaseArnl -lArNetworkingForArnl -lAriaForArnl -lSonArnl -lpthread -ldl -lrt -Xlinker -Bstatic -lstdc++ -Xlinker -Bdynamic -lpthread -ldl -lrt

robotServer: Socket.o ServerSocket.o follow.o
	$(CXX) $(CFLAGS) $(ARIA_INCLUDE) tldRobotServer.cpp  Socket.o ServerSocket.o follow.o -o robotServer $(ARIA_LINK)

follow.o: 
	$(CXX) $(CFLAGS) $(ARIA_INCLUDE) follow.cpp -c -o follow.o $(ARIA_LINK)

clean:
	rm -f *.o
	rm robotServer
