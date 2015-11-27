#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netdb.h>
#include <unistd.h>

#define BUF_SIZE_ID 2

typedef struct {
	struct sockaddr_in serverAddr;
	socklen_t addr_size;
	int clientSocket;
	char id[BUF_SIZE_ID];
}Client;

typedef  struct {
	char* ip;
	int port;
}serveurI;

Client client;

void ConnexionToServer(serveurI* serverInfo);
void SendToServer(char* message);
char* ReceiveFromServer();
void DeconnexionFromServer(serveurI* serverInfo);
