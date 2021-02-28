//Author: Andrzej Jackowski
//Description: A C/C++ TCP Server library for creating TCP server programs on Linux
//creates an IPv4 Protocol server (AF_INET)


#include "SocketServerLib.h"
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 


//Function: initServer
//Initializes Socket Server
//ReturnParam: file descriptor for the server socket
int initServer(int* serverFileDesc, int port, sockaddr_in* address) 
{


	int opt = 1;    
	int addrlen = sizeof(*address); 

	// create socket and verfy if socket file desciptor exists (will be zero if creation oepration failed)
	// socket creation function returns a file description, in this case it points to the server
	if ((*serverFileDesc = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    } 
    
    // Forcefully attaching socket to the port 8080 
    if (setsockopt(*serverFileDesc, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) 
    { 
        perror("setsockopt");
    } 

    // setting address struct variables
    address->sin_family = AF_INET; 
    address->sin_addr.s_addr = INADDR_ANY; 
    address->sin_port = htons( port ); 
    
    //bind socket to the address and port
    if (bind(*serverFileDesc, (struct sockaddr *)address, sizeof(*address))<0) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 

    if (listen(*serverFileDesc, 3) < 0) 
    { 
        perror("listen"); 
        exit(EXIT_FAILURE); 
    }
}
//Function: initServer
//Initializes Socket Server
//Param: serverFileDesc - Socket File descriptot
//ReturnParam: newSocketFD -  file descriptor for socket connection

int waitForConnection(int* serverFileDesc, int* connectFileDesc, sockaddr_in* address)
{

    int addrlen = sizeof(*address); 
   	//listen for client connection
    
    
    printf("Listening for connections \r\n");


    if ((*connectFileDesc = accept(*serverFileDesc, (struct sockaddr *)address, (socklen_t*)&addrlen))<0) 
    { 
        perror("accept"); 
        exit(EXIT_FAILURE); 
    } 

}

//send data to client after connection established
//Param
//		socket - file descriptor of socket connection
//		data - data to be sent to client
int sendData(int* socket, char* data)
{
	send(*socket, data, strlen(data),0);
}


// receive data from client
// Param
//		socket - file descriptor of socket connection
//		buffer - data from the client
// 		maxlength - maximum amount of data to read into buffer
int recvData(int* socket, char* buffer)
{
	read( *socket , buffer, sizeof(buffer));
}


//closes socket conenction
//Param: serverFileDesc - Socket File descriptor
//ReturnParam: newSocketFD -  file descriptor for socket connection
int closeSocket(int* serverFileDesc, int* connectFileDesc)
{
    close(*serverFileDesc);
    close(*connectFileDesc);
}