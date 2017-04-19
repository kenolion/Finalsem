#include "Network.h"

////////////////////////////////////////////////////////////////////////SERVER//////////////////////////////////////////////////////////////////////////

int Network::initializeWinSock()
{

	WSADATA wsaData;
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData); //Winsock Initialization, this WSAStartup function us used to intiate the use of WS2_32.dll, WSAData structure contains information about the Windows Sockets implementation. The Makeword(2,2) parameter makes a request of version 2.2 of Winsock on the system, and sets the passed version as the highest version of Windows Sockets support that the caller can use.

	if (iResult != 0) {
		printf("WSAStartup failed : %d\n", iResult);
		return 1;
	}
	sendbuf = "  ";
	return 0;
}

void Network::startClientThread(HANDLE thread, unsigned threadID)
{
	thread = (HANDLE)_beginthreadex(NULL, 0, &Network::clientThread, this, 0, &threadID);

}

void Network::startServerThread(HANDLE thread, unsigned threadID)
{
	thread = (HANDLE)_beginthreadex(NULL, 0, &Network::serverThread, this, 0, &threadID);
}

unsigned __stdcall  Network::serverThread(void *pArguments)
{
	//sendbuf = " MESSAGE FROM SERVER\n";
	Network * p_network = static_cast<Network*>(pArguments);

	do
	{
		p_network->iResult = recv(p_network->ClientSocket, p_network->recvbuf, p_network->recvbuflen, 0);
		std::cout << " thread is still running";
		if (p_network->iResult == SOCKET_ERROR) {
			printf("send failed as server: %d\n", WSAGetLastError());
			closesocket(p_network->ClientSocket);
			_endthreadex(0);
			WSACleanup();
		}

		if (p_network->iResult > 0) {
			printf("Bytes received: %d\n", p_network->iResult);
			printf(p_network->recvbuf);
			// Echo the buffer back to the sender
			p_network->iSendResult = send(p_network->ClientSocket, p_network->recvbuf, p_network->iResult, 0);
			//*p_network->recvbuf = 0;
			if (p_network->iSendResult == SOCKET_ERROR) {
				printf("send failed with error: %d\n", WSAGetLastError());
				closesocket(p_network->ClientSocket);
				WSACleanup();
				_endthreadex(0);
				return 1;
			}
			printf("Bytes sent: %d\n", p_network->iSendResult);
		}
		else if (p_network->iResult == 0)
			printf("Connection closing...\n");
		else {
			printf("recv failed with error: %d\n", WSAGetLastError());
			closesocket(p_network->ClientSocket);
			WSACleanup();
			_endthreadex(0);
			return 1;
		}


	} while (p_network->iResult > 0);
	return 0;

}

unsigned __stdcall  Network::clientThread(void *pArguments)
{
	//sendbuf = "MeSSAGE FROM CLIENT\n";
	Network * p_network = static_cast<Network*>(pArguments);

	do
	{
		p_network->iResult = recv(p_network->ConnectSocket, p_network->recvbuf, p_network->recvbuflen, 0);
		/*if (sendbuf != 0) {
			iResult = send(ConnectSocket, sendbuf, (int)strlen(sendbuf), 0);
			printf("Bytes Sent as Client : %ld\n", iResult);
			sendbuf = 0;

		}*/
		if (p_network->iResult > 0)
			printf("Bytes received: %d\n", p_network->iResult);
		else if (p_network->iResult == 0)
			printf("Connection closed\n");
		else
			printf("recv failed with error: %d\n", WSAGetLastError());

		if (p_network->iResult != 0)
		{
			printf(p_network->recvbuf);
		}



	} while (p_network->iResult > 0);
	return 0;

}

void Network::sendData(int clientType)
{
	if ((int)strlen(sendbuf.c_str())> 0) {
		if (clientType == 1) {
			iResult = send(ClientSocket, sendbuf.c_str(), (int)strlen(sendbuf.c_str()), 0);
			printf("Bytes Sent as Server : %ld\n", iResult);
		}
		else if(clientType == 2){
			iResult = send(ConnectSocket, sendbuf.c_str(), (int)strlen(sendbuf.c_str()), 0);
			printf("Bytes Sent as Client : %ld\n", iResult);
		}
	
		sendbuf.clear();
		sendbuf = "  ";   //sets the size of the string so that I dont get string subscript out of range
	}

}



int Network::resolveAddressAndPort(PCSTR hostIpAddress)
{
	ZeroMemory(&hints, sizeof(hints));

	hints.ai_family = AF_UNSPEC;	//<-Internet address family is unspecified so that either an IPv6 or Ipv4 address can be returned. 
	//AF_INET = IPV4
	//AF_INET6 = IPV6

	hints.ai_socktype = SOCK_STREAM;
	//SOCK_STREAM = This socket type uses the Transmission Control Protocol (TCP) for the Internet address family (AF_INET or AF_INET6).
	//SOCK_DGRAM = This socket type uses the User Datagram Protocol (UDP) for the Internet address family (AF_INET or AF_INET6).

	hints.ai_protocol = IPPROTO_TCP; // <- This can be changed to TCP or UDP.
	//IPPROTO_TCP == TPC
	//IPPROTO_UDP == UDP

	hints.ai_flags = AI_PASSIVE;
	//The socket address will be used in a call to the bind function.

	//Resolve the local adderss and port to be used by the server
	iResult = getaddrinfo(hostIpAddress, DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed : %d\n", iResult);
		WSACleanup(); // WSACleanup is used to terminate the use of WS2_32 DLL.
		return 1;
	}
	return 0;
}

int Network::createServerSocket()
{
	ListenSocket = socket(result->ai_family,
		result->ai_socktype,
		result->ai_protocol);
	if (ListenSocket == INVALID_SOCKET) {
		printf("Error at socket(): %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		return 1;
	}
	return 0;

}

int Network::bindServerSocket()
{

	iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR)
	{
		printf("bind failed with error : %d\n", WSAGetLastError());
		freeaddrinfo(result);
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	freeaddrinfo(result);
	return 0;
}

int Network::listenOnSocket()
{
	if (listen(ListenSocket, SOMAXCONN) == SOCKET_ERROR) //Turns socket into a listening state.
	{
		printf("Listen failed with error : %ld\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}
	printf("Server is now listening.\n");
	return 0;
}

int Network::acceptConnection()
{

	ClientSocket = accept(ListenSocket, NULL /*result->ai_addr*/, NULL /*&addrlen*/);
	if (ClientSocket == INVALID_SOCKET) {
		printf("Failed to accept the client's connection : %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}
	printf("Client Connected!\n");
	closesocket(ListenSocket);
	return 0;



}



int Network::disconnectAndShutdownSocket()
{	//shutdown the send half of the connection since no more data will be sent
	iResult = shutdown(ClientSocket, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		printf("shutdown failed : %d\n", WSAGetLastError());
		closesocket(ClientSocket);
		WSACleanup();
		return 1;
	}
	//cleanup
	closesocket(ClientSocket);
	WSACleanup();

	return 0;
}




////////////////////////////////////////////////////////////////////////CLIENT//////////////////////////////////////////////////////////////////////////


int Network::createClientSocket(PCSTR ipAddress)
{
	//if (argc != 2) {
	//	printf("usage: %s server-name\n", argv[0]);
	//	return 1;
	//}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	// Resolve the server address and port
	iResult = getaddrinfo(ipAddress, DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed: %d\n", iResult);
		WSACleanup();
		return 1;
	}

	// Attempt to connect to the first address returned by
	// the call to getaddrinfo
	ptr = result;

	// Create a SOCKET for connecting to server
	ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

	if (ConnectSocket == INVALID_SOCKET) {
		printf("Error at socket(): %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		return 1;
	}

	return 0;

}

int Network::connectClientSocket()
{
	// Connect to server.
	iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		closesocket(ConnectSocket);
		ConnectSocket = INVALID_SOCKET;
	}

	// Should really try the next address returned by getaddrinfo
	// if the connect call failed
	// But for this simple example we just free the resources
	// returned by getaddrinfo and print an error message

	freeaddrinfo(result);

	if (ConnectSocket == INVALID_SOCKET) {
		printf("Unable to connect to server!\n");
		WSACleanup();
		return 1;
	}
	printf("Client is asking to connect to server.\n");

	return 0;
}




//int Network::server()
//
//{ // Initialize Winsock
//	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
//	if (iResult != 0) {
//		printf("WSAStartup failed with error: %d\n", iResult);
//		return 1;
//	}
//
//	ZeroMemory(&hints, sizeof(hints));
//	hints.ai_family = AF_INET;
//	hints.ai_socktype = SOCK_STREAM;
//	hints.ai_protocol = IPPROTO_TCP;
//	hints.ai_flags = AI_PASSIVE;
//
//	// Resolve the server address and port
//	iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
//	if (iResult != 0) {
//		printf("getaddrinfo failed with error: %d\n", iResult);
//		WSACleanup();
//		return 1;
//	}
//
//	// Create a SOCKET for connecting to server
//	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
//	if (ListenSocket == INVALID_SOCKET) {
//		printf("socket failed with error: %ld\n", WSAGetLastError());
//		freeaddrinfo(result);
//		WSACleanup();
//		return 1;
//	}
//
//	// Setup the TCP listening socket
//	iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
//	if (iResult == SOCKET_ERROR) {
//		printf("bind failed with error: %d\n", WSAGetLastError());
//		freeaddrinfo(result);
//		closesocket(ListenSocket);
//		WSACleanup();
//		return 1;
//	}
//
//	freeaddrinfo(result);
//
//	iResult = listen(ListenSocket, SOMAXCONN);
//	if (iResult == SOCKET_ERROR) {
//		printf("listen failed with error: %d\n", WSAGetLastError());
//		closesocket(ListenSocket);
//		WSACleanup();
//		return 1;
//	}
//
//	// Accept a client socket
//	ClientSocket = accept(ListenSocket, NULL, NULL);
//	if (ClientSocket == INVALID_SOCKET) {
//		printf("accept failed with error: %d\n", WSAGetLastError());
//		closesocket(ListenSocket);
//		WSACleanup();
//		return 1;
//	}
//
//	// No longer need server socket
//	closesocket(ListenSocket);
//
//	// Receive until the peer shuts down the connection
//	do {
//
//		iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
//		if (iResult > 0) {
//			printf("Bytes received: %d\n", iResult);
//
//			// Echo the buffer back to the sender
//			iSendResult = send(ClientSocket, recvbuf, iResult, 0);

//			if (iSendResult == SOCKET_ERROR) {
//				printf("send failed with error: %d\n", WSAGetLastError());
//				closesocket(ClientSocket);
//				WSACleanup();
//				return 1;
//			}
//			printf("Bytes sent: %d\n", iSendResult);
//		}
//		else if (iResult == 0)
//			printf("Connection closing...\n");
//		else {
//			printf("recv failed with error: %d\n", WSAGetLastError());
//			closesocket(ClientSocket);
//			WSACleanup();
//			return 1;
//		}
//
//	} while (iResult > 0);
//
//	// shutdown the connection since we're done
//	iResult = shutdown(ClientSocket, SD_SEND);
//	if (iResult == SOCKET_ERROR) {
//		printf("shutdown failed with error: %d\n", WSAGetLastError());
//		closesocket(ClientSocket);
//		WSACleanup();
//		return 1;
//	}
//
//	// cleanup
//	closesocket(ClientSocket);
//	WSACleanup();
//
//	return 0;
//
//}
//
//int Network::client()
//{ // Initialize Winsock
//	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
//	if (iResult != 0) {
//		printf("WSAStartup failed with error: %d\n", iResult);
//		return 1;
//	}
//
//	ZeroMemory(&hints, sizeof(hints));
//	hints.ai_family = AF_UNSPEC;
//	hints.ai_socktype = SOCK_STREAM;
//	hints.ai_protocol = IPPROTO_TCP;
//
//	// Resolve the server address and port
//	iResult = getaddrinfo(argv[1], DEFAULT_PORT, &hints, &result);
//	if (iResult != 0) {
//		printf("getaddrinfo failed with error: %d\n", iResult);
//		WSACleanup();
//		return 1;
//	}
//
//	// Attempt to connect to an address until one succeeds
//	for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {
//
//		// Create a SOCKET for connecting to server
//		ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
//			ptr->ai_protocol);
//		if (ConnectSocket == INVALID_SOCKET) {
//			printf("socket failed with error: %ld\n", WSAGetLastError());
//			WSACleanup();
//			return 1;
//		}
//
//		// Connect to server.
//		iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
//		if (iResult == SOCKET_ERROR) {
//			closesocket(ConnectSocket);
//			ConnectSocket = INVALID_SOCKET;
//			continue;
//		}
//		break;
//	}
//
//	freeaddrinfo(result);
//
//	if (ConnectSocket == INVALID_SOCKET) {
//		printf("Unable to connect to server!\n");
//		WSACleanup();
//		return 1;
//	}
//
//	// Send an initial buffer
//	iResult = send(ConnectSocket, sendbuf, (int)strlen(sendbuf), 0);
//	if (iResult == SOCKET_ERROR) {
//		printf("send failed with error: %d\n", WSAGetLastError());
//		closesocket(ConnectSocket);
//		WSACleanup();
//		return 1;
//	}
//
//	printf("Bytes Sent: %ld\n", iResult);
//
//	// shutdown the connection since no more data will be sent
//	iResult = shutdown(ConnectSocket, SD_SEND);
//	if (iResult == SOCKET_ERROR) {
//		printf("shutdown failed with error: %d\n", WSAGetLastError());
//		closesocket(ConnectSocket);
//		WSACleanup();
//		return 1;
//	}
//
//	// Receive until the peer closes the connection
//	do {
//
//		iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
//		if (iResult > 0)
//			printf("Bytes received: %d\n", iResult);
//		else if (iResult == 0)
//			printf("Connection closed\n");
//		else
//			printf("recv failed with error: %d\n", WSAGetLastError());
//
//	} while (iResult > 0);
//
//	// cleanup
//	closesocket(ConnectSocket);
//	WSACleanup();
//
//	return 0;
//}

Network::Network()
{
}


Network::~Network()
{
}
