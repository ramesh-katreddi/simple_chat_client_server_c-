#include <iostream>
#include "NetworkHost.h"
using namespace std;
#pragma comment(lib, "Ws2_32.lib")

/* constructors */
NetworkHost::NetworkHost()
{

}
/*
	Function: NetworkHost
	Purpose:
	setup the port number and initialize the socket and address info 
*/

NetworkHost::NetworkHost(int portNumber)
{
	setPortNumber(portNumber);
	m_socket = INVALID_SOCKET;
	m_addressInfo = NULL;

}
/*
	Function: initializeSocket
	Purpose:
	initialize the socket.
	This involves initializing the winsock
	and getting the addressinfo depending on port and server.
	in our case server is localhost 127.0.0.1 so marking it to null
	it automatically loops back the messages
*/

bool NetworkHost::initializeSocket()
{
	bool retVal = false;
	
	if(initializeWinsock())
	{
		getServerAddressInfo();
	}
	if(m_addressInfo)
	{
		retVal = true;
	}
	return retVal;
}
/*
	Function: initializeWinsock
	Purpose:
	basic step for using sockets on windows
*/
int NetworkHost::initializeWinsock()
{
	int retVal;
	// Initialize Winsock
	retVal = WSAStartup(MAKEWORD(2,2), &m_wsaData);
	if (retVal != 0) {
	    printf("WSAStartup failed: %d\n", retVal);
	}	
	return !retVal;
}

/*
	Function: getServerAddressInfo
	Purpose:
	basic step for using sockets on windows
	THIS PART OF CODE HAS BEEN TAKEN FROM MSDN.
*/
void NetworkHost::getServerAddressInfo()
{
	struct addrinfo hints;
	// setup essentials to get server info
	ZeroMemory(&hints, sizeof (hints));
    hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	
	int retVal;
    char portstring[10];
    sprintf(portstring, "%d", m_portNumber);
	
    retVal = getaddrinfo(NULL, portstring, &hints, &m_addressInfo);
    if ( retVal != 0 ) {
        printf("getaddrinfo failed with error: %d\n", retVal);
        WSACleanup();
    }
}
/*
	Function: reportError
	Purpose:
	Cleanup functions in case of any error.
	close the socket 
	display error message
	clean the winsock
*/

void NetworkHost::reportError(char* whatFailed)
{
	cout<<whatFailed<<" failed "<<WSAGetLastError()<<endl;
	closesocket(m_socket);
	WSACleanup();
}