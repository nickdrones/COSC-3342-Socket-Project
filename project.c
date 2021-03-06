#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
int randperm(int *, int);

struct deck
{
	int cards[52];
};

//function to send a message, makes body of code nice and short
void sendMessage(int socketID, char *messageForClient)
{
	char sendBuffer[4096];
    sprintf(sendBuffer, messageForClient);
    int sendSuccess = write(socketID , sendBuffer , strlen(sendBuffer));
}

//function to send content to server, NOT simple text message
void sendIntArray(int socketID, int arrayToSend[52])
{
    int sendSuccess = write(socketID , arrayToSend , 208);
}

//function to send cards to client
void sendCards(int socketID){
		struct deck deckOfCards;
        int i;
		for (i=0;i<52;i++)
        {
                deckOfCards.cards[i]=i;
        }
        randperm(deckOfCards.cards,52);
		sendIntArray(socketID, deckOfCards.cards);
}

int main(int argc, char *argv[])
{
        int firstPort=atoi(argv[1]);

		/////////////////////////////////
		/// Set Up Socket
		/////////////////////////////////
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
		/////////////////////////////////
		/// Socket Setup Complete
		/////////////////////////////////
		
		//Listen for incoming connection and accept connection
        int listenState1=listen(socketState1, 5);
        int acceptConnection1=accept(socketState1,(struct sockaddr *)&serverParameters1,(socklen_t*)&addrlen1);

		//Create buffer to read command from client
		char buffer[1024]={0};
        int readToBuffer = read(acceptConnection1, buffer, 1024);


                //printf("%s\n", buffer);
				
				//create string for desired command, then use strncmp to compare only the first 4 char of buffer to desired command
                char* commandToGet="deal";
                if(strncmp(buffer,commandToGet,4)==0)
                {
                        printf("Deal Command Accepted\n");
                        sendCards(acceptConnection1);
                        exit(0);
                }
                else
                {
                        printf("Invalid Command\n");
                        exit(0);
                }

}