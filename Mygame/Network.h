#ifndef NETWORK_H
#define NETWORK_H

#include <WinSock2.h> //Contains most of the Winsock Functions, structures and definitions. Also, the Winsock2.h header file includes core elements from the Windows.h header file. Thus, #define WIN32_LEAN_AND_MEAN is included.
#include <WS2tcpip.h> //Contains definitions introduced in the WinSock 2 Protocol-Specific Annex document for TCP/IP that includes newer functions and structures used to retrive IP Addresses.
#include <stdio.h> // <- has standard input and output, specifically the printf() function. 
#include <stdlib.h>
//#pragma comment(lib, "ws2_32.lib") //<- indicates to the linker that Ws2_32.lib is needed. (Remember to link Ws2_32.lib in your project)
//#pragma comment (lib, "Mswsock.lib")
//#pragma comment (lib, "AdvApi32.lib")

#define DEFAULT_PORT "27015"  // <- Used in Part 1, Winsock Initialization.
#define DEFAULT_BUFLEN 512

class Network
{
private :
	
	int iResult;
	int iSendResult;
	int argc;
	char **argv;

	struct addrinfo *result = NULL,        //An "addrinfo" object with a "sockaddr" structure. 
					*ptr = NULL,		   //The "sockaddr" structure includes the IP address of the server that the client will try to connect to and the port number.
		           	hints;

	SOCKET ListenSocket = INVALID_SOCKET;
	SOCKET ClientSocket = INVALID_SOCKET; // Socket for accepting connections from clients.

	SOCKET ConnectSocket = INVALID_SOCKET;

	int recvbuflen = DEFAULT_BUFLEN;
	char * sendbuf = "this is a test";
	char recvbuf[DEFAULT_BUFLEN];


	//int server();
	//int client();

public:
	int initializeWinSock();

	//SERVER
	int resolveAddressAndPort();
	int createServerSocket();
	int bindServerSocket();
	int listenOnSocket();
	int acceptConnection();
	int receiveUntilPeerShutdown();
	int disconnectAndShutdownSocket();

	//CLIENT (needs to pass in ip number of server)
	int createClientSocket();
	int connectClientSocket();
	int sendAndReceiveDataAsClient();
	int disconnectClientSocket();

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