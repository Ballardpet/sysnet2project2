main: main.o httpServer.o
	g++ -g -Wall main.o httpServer.o -o main

main.o: main.cpp
	g++ -g -Wall -c main.cpp -o main.o

httpServer.o: httpServer.hpp httpServer.cpp
	g++ -g -Wall -c httpServer.hpp httpServer.cpp

clean:
	rm *.o *.gch main