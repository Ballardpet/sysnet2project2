# sysnet2project2
Peter Ballard & Nan Stephanishen
Systems & Networks II
Project 2
README

Setup and compilation
1. Download and unzip the file from Canvas.
2. This submission should include
    *clientMain.cpp
    *httpCLient.cpp
    *httpClient.hpp
    *httpServer.cpp
    *httpServer.hpp
    *img.jpg (provided from canvas)
    *index.html (provided from canvas)
    *Makefile
    *protocols.pdf
    *README.md (this file)
    *serverMain.cpp
    *ss1.png
    *ss2.png
    *ss3.png
    *testPresence.html (provided from canvas)
3. Environment: This program has been tested in the multi-platform lab and will run there
4. This program includes a Makefile. At the command line in Linux, type make all. 
    The program will compile an two executables name "serverMain" and "clientMain"

Running the program: Be sure that img.jpg, index.html, and testPresence.html are in the same directory as the executable. Issue the command "./serverMain" to start the server. In another terminal window, execute the command "./clientMain". No command line arguments are required or checked.

Connecting to the server: In the terminal running "clientMain", enter the ip address "127.0.0.1" and the port "60069" when promted to connect to the server. You may then enter filenames as prompted. There will then be two forms of output. Text will be displayed on the terminals for both the client and the server related to the messages sent between them. A file will then be created based off of the response to the client's request.