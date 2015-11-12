# simple_chat_client_server_c++
A simple chat client server application that was developed during interview process of one of the reputed company.

ChatApplication:

Usage:

Compile ChatApplicatoin.cpp

Run:

ChatApplication "SERVER" PORT_NUMBER
ChatApplication "CLIENT" PORT_NUMBER

Files:

Both Servers/Clients are essentially NetworHosts. 

NetworkHost.h
NetworkHost.cpp ParentClass ->Contains the abstraction of client and server side functionalities and entities.

ChatClient.h
ChatClient.cpp  ChatClient Object (sub class of network host)->Connection mechanism and Functionalities of client 

ChatServer.h
ChatServer.cpp  ChatServer Object (sub class of network host) ->Connection mechanism and functionalities of server

ChatApplicatoin.h
ChatApplication.cpp Singleton object which is Main applicatoin and handles the creation of client/server and input validation.

CommunicaitonLogger.h
CommunicationLogger.cpp --> Singleton sintance for logging TODO.

TODO's/Known Issues:

Communication Logger :  (Could not do because of lack of time).

This is a singleton object to write into files. 
In case two different threads on server tries to access this, application crashes. We need to use mutex mechanism or glog library provided by google.

Most of the constants are kept in different files ( Some more needs to be moved).

Input validation for port number limit.

Enhancements:

Need to port it to Unix.
Whole connection process would be same but it is easy to handle that without threads by using Fork()(Know this but do not have time to install ubuntu and write and test).

