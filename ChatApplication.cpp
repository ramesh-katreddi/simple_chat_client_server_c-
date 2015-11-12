#include<iostream>
#include "Constants.h"
#include "ChatApplication.h"
using namespace std;

ChatApplication* ChatApplication::pChatAppSingleton= NULL;

/*
Constructor
*/
ChatApplication::ChatApplication()
{
}

/*
	Function: getInstance
	Purpose:
	If there is an instance existing already dont create new 
*/

ChatApplication* ChatApplication::getInstance()
{
    boost::mutex::scoped_lock lock(m_mutex);
    if (pChatAppSingleton== NULL) {
		pChatAppSingleton = new ChatApplication();
	}
	return pChatAppSingleton;
}

/*
	Function: createClient
	Purpose:
	This function creates client on given port 
*/

ChatClient* ChatApplication::createClient(int port)
 {
	 ChatClient *chatClient = new ChatClient(port);
	 return chatClient;
 }

/*
	Function: createServer
	Purpose:
	This function creates server on given port 
*/
 ChatServer* ChatApplication::createServer(int port)
 {
	ChatServer *chatServer =  new ChatServer(port);
	return chatServer;
 }

/*
	Function: isInteger
	Purpose:
	Utility function to validate the input
*/
// Todo-- Check for integer limit 
bool isInteger(char const *c) {
   while (*c) {
     if (!isdigit(*c++)) return false;
   }
   return true;
}

/*
	Function: Main
	Purpose:
	Entry function for the whole project
	Arguments:
	Type : "SERVER"/"CLIENT"
	port : Any integer
*/
 
int main(int argc, char* argv[])
{
	
	cout<<"---------------------------------"<<endl;
	cout<<"  WELCOME TO CHAT APPLICATION  "<<endl;
	cout<<"---------------------------------"<<endl;

	int port;
	if(argc < 2)
	{
		cout<<INVALID_ARGUMENTS<<endl; 
	}
	else 
	{
		if (isInteger(argv[2]) ) // If the port entered is valid
		{
			port = atoi(argv[2]);
			ChatApplication *m_chatApp = ChatApplication::getInstance();
			if(!m_chatApp)
			{
				cout<<APP_INIT_FAILED;
			}
			if(strcmp(argv[1],"CLIENT") == 0)
			{
				cout<<CREATE_CLIENT<<port<<endl;
				
				// Create a new Client on Port number given
				ChatClient *chatClient = m_chatApp->createClient(port);
				
				// This function takes care of the setting up the whole connection for client
				if(chatClient)
					chatClient->setupConnection();
				
			}
			else if(strcmp(argv[1],"SERVER") == 0)
			{
				cout<<CREATE_SERVER<<port<<endl;
				
				ChatServer* chatServer = m_chatApp->createServer(port);
				// Create the server and setup the connection . It involves bind listen accept procedure 
				//and also response mechanism.
				//in case it fails ask user again if he wants to add new port
				if(chatServer && !chatServer->setupConnection())
				{
					cout<<ENTER_DIFFERENT_PORT<<endl;
					cin>>port;
					ChatServer* newChatServer = m_chatApp->createServer(port);
					if(newChatServer)
						newChatServer->setupConnection();
				}
			}
			else 
			{
				cout<<INVALID_ARGUMENTS<<endl;
			}
		}
		else
		{
			cout<<INVALID_ARGUMENTS<<endl;
		}		
		
	}

	return 0;
}