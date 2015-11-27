/* Créer par GAMA Filipe
Pour le projet de robotique en 3ème année de Licence à l'Université de Cergy-Pontoise. */

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
#include "client.h"

/* default value/easi to change variables */
#define IP_SERV "10.20.60.145" // IP of the server we want to connect to.
#define PORT 9930 // Port the server is listening to, waiting for a client to connect.

#define BUF_SIZE_INIT 4 // size of message to send to the server in order to connect the two.
#define BUF_SIZE_ANSW 10 // size of the message received from the server.
#define NUMBER_OF_TRIES 10 // number of times we try to communicate with the serveur. Sort of a Time To Live.

/* global variables */
extern Client client; //client-serveur connexion.

void ConnexionToServer(serveurI* serverInfo) {

	char* connexionMessage = "new";
	int numberOfTries = NUMBER_OF_TRIES;


	/* set default IP and PORT if it hasn't been given by the user. */
	if(serverInfo->ip == NULL) {
		serverInfo->ip = IP_SERV;
	}
	if(serverInfo->port == -1) {
		serverInfo->port = PORT;
	}

	/* Create UDP socket. */
	client.clientSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); // IPPROTO_UDP can be replaced by 0.

	/* Configure settings in address struct. */
	client.serverAddr.sin_family = AF_INET;
	client.serverAddr.sin_port = htons(serverInfo->port);
	client.serverAddr.sin_addr.s_addr = inet_addr(serverInfo->ip);
	memset(client.serverAddr.sin_zero, '\0', sizeof client.serverAddr.sin_zero);

	/* Initialise size variable to be used later on. */
	client.addr_size = sizeof client.serverAddr;

	/* Add a timeout to rcfrom function */
	struct timeval tv;
	tv.tv_sec = 5; // 5 seconds timeout.
	tv.tv_usec = 0; // Not initilising because it can cause strange errors. 

	setsockopt(client.clientSocket, SOL_SOCKET, SO_RCVTIMEO, (char *)&tv, sizeof(tv));

	while((client.id == NULL || strlen(client.id) != 2) && (numberOfTries > 0)) {
		sendto(client.clientSocket, connexionMessage, BUF_SIZE_INIT, 0, (struct sockaddr *)&client.serverAddr, client.addr_size);
		recvfrom(client.clientSocket, client.id, BUF_SIZE_ID, 0, NULL, NULL);
		/* May need to multiply by 8 the BUF_SIZE in sendto/rcvfrom. May need to do "- 1" to BUF_SIZE in sendto/rcvfrom. */
		numberOfTries--;
	}
	printf("%s\n", client.id);
}

void sendToServeur(char* baseMessage) {

	char* message;
	int tailleMessage = (strlen(baseMessage) + strlen(client.id) + strlen("dat") + 2);
	message = malloc(tailleMessage*sizeof(char*));
	int numberOfTries = NUMBER_OF_TRIES;
	char* answer;
	answer = malloc(3*sizeof(char));
	/* Protocole de message : Ce qui est en parenthèses sont les variables, les parenthèses de sont pas à mettre dans le message
		dat(client.id),P,(Pan),T,(Tilt) */

	strcat(message, "dat");
	strcat(message, client.id);
	strcat(message, ",");
	strcat(message, baseMessage);
	do{
		sendto(client.clientSocket, message, tailleMessage, 0, (struct sockaddr *)&client.serverAddr, client.addr_size);
		recvfrom(client.clientSocket, answer, BUF_SIZE_ANSW, 0, NULL, NULL);
		/* May need to multiply by 8 the BUF_SIZE in sendto/rcvfrom. May need to to "-1" to BUF_SIZE in sendto/rcvfrom.*/
		numberOfTries--;
	}while((strcmp(answer, "ok") != 0) && (numberOfTries > 0));
}

void DeconnexionFromServer(serveurI* serverInfo) {
	close(client.clientSocket);
}

int main () {
	serveurI serveurinfo;
	serveurinfo.ip = IP_SERV;
	serveurinfo.port = PORT;

	ConnexionToServer(&serveurinfo);

	char* message = "p,80,t,-10";
	sendToServeur(message);

	DeconnexionFromServer(&serveurinfo);

	return 0;
 }
