#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void sendMessage(int socketID, char *messageForClient)
{
	char sendBuffer[1024];
    sprintf(sendBuffer, messageForClient);
    int sendSuccess = send(socketID , sendBuffer , strlen(sendBuffer),0);
}

int main(int argc, char *argv[])
{
	// ./client <ipaddr> <portnum>
	
	char *IPaddr=argv[1];
	int portNum=atoi(argv[2]);
	
	struct sockaddr_in serverToConnect;
	
	int socketState=socket(AF_INET, SOCK_STREAM, 0);
	if(socketState<0)
    {
		printf("Failed to create socket, exiting...\n");
        exit(0);
    }
	
	serverToConnect.sin_family = AF_INET;
    serverToConnect.sin_port = htons(portNum);
	
	int inetAddr = inet_pton(AF_INET, IPaddr, &serverToConnect.sin_addr);
	if(inetAddr<0)
    {
		printf("Failed to init connection, exiting...\n");
        exit(0);
    }
	
	int connectToServer = connect(socketState,(struct sockaddr *)&serverToConnect, sizeof(serverToConnect));
	if(connectToServer<0)
    {
		printf("Failed to connect to server, exiting...\n");
        exit(0);
    }
	
	sendMessage(socketState, "deal\n");
	
	//char buffer[4096]={0};
	int arrayOfInts[52]={0};
    int readToBuffer = recv(socketState, arrayOfInts, 4096, 0);
	//printf("%s\n", buffer);
	int i;
	for (i=0;i<52;i++)
    {
		printf("%d\n",arrayOfInts[i]);
    }
	
}