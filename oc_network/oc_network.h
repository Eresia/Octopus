#ifndef OC_NETWORK
#define OC_NETWORK


#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


#define BUFLEN 512
#define PORT 9930
#define NUMBER_DATA 6

//Types of messages
#define NEW_CONNEXION "new"
#define DATA "dat"
#define PAN "pan"
#define TILT "tilt"

typedef struct oc_message{
  int ID;
  char *name;
  int is_active;

  int read;
} oc_message;

typedef struct Data{
    char* pan;
    char* id;
    char* tilt;
} Data;

void *oc_server(void *);
char** whichData(Data , char* );
char** dividedString(char* , int );

#endif /*OC_NETWORK*/
