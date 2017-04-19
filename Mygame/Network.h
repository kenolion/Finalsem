#ifndef NETWORK_H
#define NETWORK_H

#include <WinSock2.h> //Contains most of the Winsock Functions, structures and definitions. Also, the Winsock2.h header file includes core elements from the Windows.h header file. Thus, #define WIN32_LEAN_AND_MEAN is included.
#include <WS2tcpip.h> //Contains definitions introduced in the WinSock 2 Protocol-Specific Annex document for TCP/IP that includes newer functions and structures used to retrive IP Addresses.
#include <stdio.h> // <- has standard input and output, specifically the printf() function. 
#include <stdlib.h>
#include <string>
#include <iostream>
#include <process.h>

//#pragma comment(lib, "ws2_32.lib") //<- indicates to the linker that Ws2_32.lib is needed. (Remember to link Ws2_32.lib in your project)
//#pragma comment (lib, "Mswsock.lib")
//#pragma comment (lib, "AdvApi32.lib")

#define DEFAULT_PORT "27015"  // <- Used in Part 1, Winsock Initialization.
#define DEFAULT_BUFLEN 512


class Network
{
private:

	int iResult;
	int iSendResult;
	int argc;
	char **argv;

	struct addrinfo *result = NULL,        //An "addrinfo" object with a "sockaddr" structure. 
		*ptr = NULL,		   //The "sockaddr" structure includes the IP address of the server that the client will try to connect to and the port number.
		hints;

	int addrlen = sizeof(result->ai_addr);
	SOCKET ListenSocket = INVALID_SOCKET; //Listening Socket
	SOCKET ClientSocket = INVALID_SOCKET; // Socket for accepting connections from clients.
	SOCKET ConnectSocket = INVALID_SOCKET;




	//int server();
	//int client();

public:
	
	int initializeWinSock();
	//THREADS
	//typedef void(Network::*pfunc)(void);
	void startClientThread(HANDLE thread, unsigned threadID);
	void startServerThread(HANDLE thread, unsigned threadID);
	static unsigned __stdcall  serverThread(void *pArguments);
	static unsigned __stdcall  clientThread(void *pArguments);
	void sendData(int clientType);

	char serverBuffer[256];
	int serverBufferLength;
	char clientBuffer[256];
	int clientBufferLength;

	//SERVER
	int resolveAddressAndPort(PCSTR hostIpAddress);
	int createServerSocket();
	int bindServerSocket();
	int listenOnSocket();
	int acceptConnection();

	char msg[256];


	int disconnectAndShutdownSocket();

	//CLIENT (needs to pass in ip number of server)
	int createClientSocket(PCSTR ipAddress);
	int connectClientSocket();

	int recvbuflen = DEFAULT_BUFLEN;
	std::string sendbuf;
	char recvbuf[DEFAULT_BUFLEN];
	char prevrecbuf[DEFAULT_BUFLEN];

	std::string test;

	Network();
	~Network();
};

#endif










/* SERVER

1)Initialize Winsock. - ONLY ONCE -
2)Create a socket.
3)Bind the socket.
4)Listen on the socket for a client.
5)Accept a connection from a client.
6)Receive and send data.
7)Disconnect.

*/

/* CLIENT

1)Initialize Winsock. - ONLY ONCE -
2)Create a socket.
3)Connect to the server.
4)Send and receive data.
5)Disconnect.

*/