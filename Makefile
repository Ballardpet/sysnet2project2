CXX = g++
CXXFLAGS = -g -Wall -pthread -std=c++2a

SERVER_OBJS = serverMain.o httpServer.o
CLIENT_OBJS = clientMain.o httpClient.o

all: serverMain clientMain

serverMain: $(SERVER_OBJS)
	$(CXX) $(CXXFLAGS) -o serverMain $(SERVER_OBJS)

serverMain.o: serverMain.cpp httpServer.hpp
	$(CXX) $(CXXFLAGS) -c serverMain.cpp

httpServer.o: httpServer.cpp httpServer.hpp
	$(CXX) $(CXXFLAGS) -c httpServer.cpp

clientMain: $(CLIENT_OBJS)
	$(CXX) $(CXXFLAGS) -o clientMain $(CLIENT_OBJS)

clientMain.o: clientMain.cpp httpClient.hpp
	$(CXX) $(CXXFLAGS) -c clientMain.cpp

httpClient.o: httpClient.cpp httpClient.hpp
	$(CXX) $(CXXFLAGS) -c httpClient.cpp

clean:
	rm -f *.o *.gch serverMain clientMain