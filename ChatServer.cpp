#include <iostream>
#include <process.h>
#include "ChatServer.h"
#include "Constants.h"
#pragma comment(lib, "Ws2_32.lib")
using namespace std;

/* constructors */
ChatServer::ChatServer()
{
}

ChatServer::ChatServer(int portNumber):NetworkHost(portNumber)
{
}

/*
	Function: setupConnection
	Purpose:
	This is a must function for any network agent.
	In server case.
	It is as following.
	We need to bind the socket and keep listening on the port
	and once some client comes we need to accept connections.

	IF ANY OF THE FUNCTIONS FAIL WE RETURN
*/

bool ChatServer::setupConnection()
{
	if(initializeSocket()) // common for all network agents. 
	{
		if(createSocket()) // creates sockets
		{
			if(BindToPort()) // binding
			{
				if(ListenOnPort()) // listening
				{
					acceptClients(); // accept clients
					return true;
				}
		
			}
		}
	}
	return false;
}
/*
	function: createSocket
	purpose: Pure virtual function createsocket.
	Just creates a socket
*/
bool ChatServer::createSocket()
{
	if(!m_addressInfo) 
		return false;

	m_socket = socket(m_addressInfo->ai_family, m_addressInfo->ai_socktype, m_addressInfo->ai_protocol);
	
	if (m_socket == INVALID_SOCKET) 
	{
		freeaddrinfo(m_addressInfo);
		reportError("createSocket");
		return false;
	}
	
	return true;	
}
/*
	function: BindToPort
	purpose: bind to port

*/
bool ChatServer::BindToPort()
{
    int retVal = bind( m_socket, m_addressInfo->ai_addr, (int)m_addressInfo->ai_addrlen);
    
	if (retVal == SOCKET_ERROR) {
		reportError("bind");
		return false;
    }
	freeaddrinfo(m_addressInfo);
	return true;
}
/*
	function: ListenOnPort
	purpose: listen on port
*/
bool  ChatServer::ListenOnPort()
{
	if ( listen( m_socket, SOMAXCONN ) == SOCKET_ERROR ) {
	
		reportError("listen");
		return false;
	}
	return true;
}
/*
	function: acceptClients
	purpose: accept clients
	for each of the client that comes in create a thread 
	and serve the requests.
*/

void  ChatServer::acceptClients()
{
	SOCKET ClientSocket = INVALID_SOCKET;
	
	while ((ClientSocket = accept(m_socket, NULL, NULL))) 
	{	
		// *** IMPORTANT_NOTE***
		/*Never pass variable on stack to different thread as its life time might end. Create a variable on heap and send*/    
		SOCKET *param = (SOCKET *)malloc(sizeof(SOCKET));
		*param = ClientSocket; 
		HANDLE hThread = (HANDLE)_beginthread(&ChatServer::serveTheClient, 0, (void*) param);
    }
	
	if (ClientSocket == INVALID_SOCKET) 
	{
		reportError("accept");
	}
}
/*
	function: serveTheClient
	purpose: 
	This is where we are sending hello in reply
	to each of the client's messages.

*/
void ChatServer::serveTheClient (LPVOID lpParameter)
{
    SOCKET *AcceptSocket = (SOCKET*)lpParameter;
	
    int bytesSent;
    int bytesRecv = SOCKET_ERROR;
    char sendbuf[DEFAULT_BUFLEN]="";
    char recvbuf[DEFAULT_BUFLEN]="";

    while (1)
    {
		ZeroMemory (recvbuf, sizeof(recvbuf));
		// recv returns number of bytes received
		bytesRecv = recv( *AcceptSocket, recvbuf, DEFAULT_BUFLEN, 0);
		if(bytesRecv > 0)
		{
			time_t curTime;
			time (&curTime);
			cout<<ctime (&curTime) << recvbuf <<endl;
			int k = sprintf(sendbuf, "%s :Hello", ctime (&curTime));
			if(k!= DEFAULT_BUFLEN)
				sendbuf[k+1] = '\0';
			//TODO-- keep this in a while loop to make sure all the data is sent.
			//not needed for our spec as we will be sending only the above string of 
			//hello with timestamp.
			bytesSent = send( *AcceptSocket, sendbuf, k, 0);
		}
	}
}