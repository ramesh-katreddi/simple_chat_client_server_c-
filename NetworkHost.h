#ifndef NETWORKHOST_H
#define NETWORKHOST_H

#include<iostream>
#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#pragma comment(lib, "Ws2_32.lib")
/*
Any clients/servers are essentially networkhosts.
These are the essential members that it needs.
*/
class NetworkHost {

public:

	int m_portNumber;
	WSADATA m_wsaData;
	SOCKET m_socket;
	struct addrinfo* m_addressInfo;
	/*
	construcots
	*/
	NetworkHost();
	NetworkHost(int port);
	// initializing socket
	bool initializeSocket();
	//craet socket
	virtual bool createSocket() = 0;
	// any network aagent needs to have a mechanism to setup connection
	virtual bool setupConnection() = 0;
	// error reporting for any network agent
	void reportError(char* whatFailed);
	
private:
	// setport number
	void setPortNumber(const int portNum) { m_portNumber = portNum;}
	int initializeWinsock();
	void getServerAddressInfo();
};
#endif