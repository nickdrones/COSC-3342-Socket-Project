#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
int randperm(int *, int);

void sendCards(int socketID){
	int some_array[52],i;
	randperm(some_array,52);
	
	printf("Before Send run\n");
	
	char *cardMessageToSend = "Beginning Deal:\n";
	int sendSuccess = send(socketID , cardMessageToSend , strlen(cardMessageToSend),0); 
	
	printf("After Send run\n");
	printf("%d\n", sendSuccess);
	//cardMessageToSend = "Card 1: 32"; 
	//sendSuccess = send(socketID , cardMessageToSend , strlen(cardMessageToSend),0); 
}

int main(int argc, char *argv[])
{
        //syntax for calling: ./socket <port for socket 1> <port for socket 2>
        char *messageToSend="Hello World";
        int firstPort=atoi(argv[1]);

        char buffer[1024]={0};


                ////////////////////////////////////////////
                // Start Socket 1, port=argv[1]
                ////////////////////////////////////////////
        struct sockaddr_in serverParameters1;
        int addrlen1=sizeof(serverParameters1);

        serverParameters1.sin_family = AF_INET;
        serverParameters1.sin_addr.s_addr = INADDR_ANY;
        serverParameters1.sin_port = htons(firstPort);

        int socketState1=socket(AF_INET, SOCK_STREAM, 0);

        int bindState1=bind(socketState1, (struct sockaddr *)&serverParameters1, addrlen1);

                if(bindState1<0)
                {
                        printf("Failed to bind Socket 1\n");
                        exit(0);
                }


                ////////////////////////////////////////////
                // Listen
                ////////////////////////////////////////////

        int listenState1=listen(socketState1, 5);

        int acceptConnection1=accept(socketState1,(struct sockaddr *)&serverParameters1,(socklen_t*)&addrlen1);

        int readToBuffer = read(acceptConnection1, buffer, 1024);


        printf("got your message\n");

		
                printf("%s\n", buffer);
                char* commandToGet="deal";
                if(strncmp(buffer,commandToGet,4)==0)
                {
                        printf("Deal Command Accepted\n");
						sendCards(socketState1);
						printf("After SendCards run\n");
                        exit(0);
                }
                else
                {
                        printf("Invalid Command\n");
                        exit(0);
                }

}