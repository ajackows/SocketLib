// Server side C/C++ program to demonstrate Socket programming 
#include "SocketServerLib.h"
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#define PORT 8080 

int main(int argc, char const *argv[]) 
{ 

	//Initiate variables
    int server_fd, new_socket;
    struct sockaddr_in address; 
    int opt = 1; 
    int addrlen = sizeof(address); 
    char buffer[1024] = {0};

    char *hello = "asshat mgee"; 
    int something = 42069;

    int code = 0;

    // initialize server, need to pass file descriptors by reference
    code = initServer(&server_fd, PORT, &address);
    if(code == 1)
    {
    	perror("Failed Connection");
    }
    printf("Socket initialized...\n");

    //wait for a client to connect
    printf("waiting for Conenction\n");
    

    //Server waits for connection from a client, poulated the new_socket file descriptor
    //new_socket file descriptor will be used for send a receive operations
    code = waitForConnection(&server_fd, &new_socket, &address);
    if(code == 1)
    {
    	perror("Failed Connection");
    }



    //below is a quick test program that sends and recives messages form a client, ending when the client sends an 'e'
    int end = 0;
    char *endMsg = "end";

    printf("conencted properly \n");
    while(end == 0)
    {
        //start read operation, waits for data from a client, stores in buffer
        //valread = read( new_socket , buffer, 1024); 

        code =  recvData(&new_socket, buffer);
        if(code == 1)
    	{
    		perror("Failed Connection");
    	}

        // prints data from client
        printf("%s\n",buffer);

        //send server response message, note that this function takes a pointer
        sendData(&new_socket, hello);

        if(buffer[0] == 'e')
        {
            printf("ending Connection\r\n");
            end = 1;
        }
    }


    closeSocket(&new_socket, &server_fd);

    return 0; 
} 
