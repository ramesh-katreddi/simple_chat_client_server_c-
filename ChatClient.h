#ifndef CHATCLIENT_H
#define CHATCLIENT_H
#include "NetworkHost.h"
/*
Purpose of this class is to wrap the functionalities of CLIENT.

SERVER AND CLIENT both are essentially NETWORK HOSTS.

So network host is an abstract class which has the entities needed for any host.

*/
class ChatClient : public NetworkHost{

public:
	/* constructors */
	ChatClient();
	ChatClient(int portnumber);
	
	// this receive function receives the input fromserver and displays (since it should not obstruct typing of user 
	//it is run in different thread
	static void receive(LPVOID lpParameter);
	// this is a pure virtual function of network host.
	//sets up the connection with server
	virtual bool setupConnection();

private:	
	virtual bool createSocket();
	void setupThreadForReceiving();
	void sendInputToServer();
	
};
#endif