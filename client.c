#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

enum suit{spades,hearts,diamonds,clubs};
enum value{ace,two,three,four,five,six,seven,eight,nine,ten,jack,queen,king};


struct card
{
	enum suit card_suit;
	enum value card_value;
};

struct card parse_card(int the_card)
{
	struct card temp_card;
	temp_card.card_suit=the_card/13;
	temp_card.card_value=the_card%13;
	return(temp_card);
};

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
	char *suitStrings[]={"Spades", "Hearts","Diamonds", "Clubs"};
	char *valueStrings[]={"Ace","Two","Three","Four","Five","Six","Seven","Eight","Nine","Ten","Jack","Queen","King"};
	for (i=0;i<52;i++)
    {
		struct card tempCardToPrint=parse_card(arrayOfInts[i]);
		int tempCardSuitNum=tempCardToPrint.card_suit;
		int tempCardValueNum=tempCardToPrint.card_value;
		printf("Card %d: %s of %s\n",i+1,valueStrings[tempCardValueNum],suitStrings[tempCardSuitNum]);
    }
	
}