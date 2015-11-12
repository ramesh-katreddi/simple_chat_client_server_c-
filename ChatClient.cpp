#include <iostream>
#include "Constants.h"
#include <process.h>
#include "ChatClient.h"
#pragma comment(lib, "Ws2_32.lib")
using namespace std;
/*constructors*/
ChatClient::ChatClient()
{
}
// actual functionality is done in parent constructor as it is same for everybody
ChatClient::ChatClient(int portNumber):NetworkHost(portNumber)
{
}

/*
	Function: setupConnection
	Purpose:
	Getting the winsock and get server address are done in parent class
	typically any client should follow this procedure.
	Get socket with server port -> connect -> and send receive messages.
	In case any of this funcitons fail our connection is unsuccessful.
	So should exit.
*/

bool ChatClient::setupConnection()
{
	if(initializeSocket())
	{
		if(createSocket())
		{
			setupThreadForReceiving();	
			sendInputToServer();
			return true;
		}
	}
	return false;
}

/*
	Function: createSocket
	Purpose:
	This is preceeded by getting a winsock and getting address
	Create a socket and connect. In case it fails client should exit
*/
bool ChatClient::createSocket()
{
	bool retVal = false;
	
	if(!m_addressInfo) // this is populated in parent class
		return retVal;

	struct addrinfo *ptr = NULL;
	// look for possible socket which we could connect otherwise bail
	for(ptr=m_addressInfo; ptr != NULL ;ptr=ptr->ai_next) 
	{
        m_socket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
     
		if (m_socket == INVALID_SOCKET) 
		{
			reportError("socket Creation");
			break;
		}

        int result = connect( m_socket, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (result == SOCKET_ERROR) {
            closesocket(m_socket);
            m_socket = INVALID_SOCKET;
            continue;
        }
        break;
    }

	freeaddrinfo(m_addressInfo);
	//if socket is not ready exit
	if (m_socket == INVALID_SOCKET) 
	{
        reportError("connect");
    }
	else return true;

	return retVal;
}
/*
	Function: setupThreadForReceiving
	Purpose:
	This fucntion setups a thread for receiving messages.
	Both sending and receiving should not be in same thread
*/

/*
	IMPORTANT_NOTE: Never pass a variable in stack to other process as we cannot guarantee its life time. 
	  So create a variable on heap and send it across the htread
*/
void ChatClient::setupThreadForReceiving()
{
	  SOCKET *arg = (SOCKET *)malloc(sizeof(SOCKET));
		*arg = m_socket; 
		
	HANDLE hThread = (HANDLE)_beginthread(&ChatClient::receive, 0,  (void*)arg);
}

/*
	Function: receive
	Purpose:
	 this funciton runs in different thread
	function to receive the messages
	and print
*/

void ChatClient::receive(LPVOID lpParameter)
{
	SOCKET *receiveSocket = (SOCKET*)lpParameter;
	char recvbuf[DEFAULT_BUFLEN];
	int  retVal = 0;
    do {
		// returns the number of bytes it received.
        retVal = recv(*receiveSocket, recvbuf, strlen(recvbuf), 0);
        if ( retVal > 0 )
		{
			//dont forget this as the buffer we get wont be null terminated
			recvbuf[retVal] = '\0';
            printf(" %s\n", recvbuf);
		}
		else if ( retVal == 0 )
            printf("Connection closed\n");
    } while(1);

    closesocket(*receiveSocket);
    WSACleanup();
	exit(0);
}

/*
	Function: sendInputToServer
	Purpose:
	this takes the input given by user and sends it to server.
*/

void ChatClient::sendInputToServer()
{
	while(1)
	{
		char sendbuf[DEFAULT_BUFLEN];
		cin.getline(sendbuf, DEFAULT_BUFLEN); // dont use cin only as it ends input stream on space also.
		// if user has given the input as exit stop the client
		if(strcmp(sendbuf,"exit")!=0)
		{
			// send the input and in case if send fails then communication is somehow lost better to quit client.
			int retVal = send( m_socket, sendbuf, (int)strlen(sendbuf), 0 );
			if (retVal == SOCKET_ERROR) {
				break;
			}
		}
		else
		{
			break;
		}
	}
    int retVal = shutdown(m_socket, SD_SEND);
    if (retVal == SOCKET_ERROR) {
        printf("shutdown failed with error: %d\n", WSAGetLastError());
        closesocket(m_socket);
        WSACleanup();
    }
	exit(0);
}