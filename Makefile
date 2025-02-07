serverMain: serverMain.o httpServer.o
	g++ -g -Wall serverMain.o httpServer.o -o serverMain

serverMain.o: serverMain.cpp
	g++ -g -Wall -c serverMain.cpp -o serverMain.o

httpServer.o: httpServer.hpp httpServer.cpp
	g++ -g -Wall -c httpServer.hpp httpServer.cpp

	

clientMain: clientMain.o httpClient.o
	g++ -g -Wall clientMain.o httpClient.o -o clientMain

clientMain.o: clientMain.cpp
	g++ -g -Wall -c clientMain.cpp -o clientMain.o

httpClient.o: httpClient.hpp httpClient.cpp
	g++ -g -Wall -c httpClient.hpp httpClient.cpp



clean:
	rm *.o *.gch serverMain clientMain