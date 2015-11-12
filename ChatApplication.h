#include<iostream>
#include "ChatClient.h"
#include "ChatServer.h"
#include "NetworkHost.h"
#include<list>
/*
	This is the main class which handles all the flows and needs to be singleton
*/
class ChatApplication 
{

public:
	//Member functions
   static ChatApplication* getInstance(); 
   //Create new client on given port
   ChatClient* createClient(int port);
   //Create new SErver on given port
   ChatServer* createServer(int port);

private:
   ChatApplication();
    
   static boost::mutex m_mutex;
   static ChatApplication* pChatAppSingleton;		// singleton instance
   const ChatApplication& operator=(const ChatApplication&);
};