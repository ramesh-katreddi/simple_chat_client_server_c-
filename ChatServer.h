#ifndef CHATSERVER_H
#define CHATSERVER_H
#include "NetworkHost.h"
/*
Purpose of this class is to wrap the functionalities of server.

SERVER AND CLIENT both are essentially NETWORK HOSTS.

So network host is an abstract class which has the entities needed for any host.

Server needs to bind to a socket then listen on it and accept any incoming client requests.

To process each client we are creating seperate thread and run servetheclient function in it
*/
class ChatServer : public NetworkHost{

public:
	/*Constructors*/
	ChatServer();
	ChatServer(int portNumber);
	// this the functionality that server is providing to the client.
	static void serveTheClient (LPVOID lpParameter);
	// this function sets up the connection 
	virtual bool setupConnection();
private:
	// Utility functions used by setupconnection
	// THESE FOUR FUCNTIONS FORM TYPICAL FLOW OF MAKING A SERVER
	virtual bool createSocket();
	bool BindToPort();
	bool ListenOnPort();
	void acceptClients();
};
#endif