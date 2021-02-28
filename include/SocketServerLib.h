//Author: Andrzej Jackowski
//Description: A C/C++ TCP Server library for creating TCP server programs on Linux


#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 


int initServer(int* serverFileDesc);
int waitForConnection(int* serverFileDesc, int* connectFileDesc);
int sendData(int* socket, char* data);
int recvData(int* socket, char* buffer, int maxLength);