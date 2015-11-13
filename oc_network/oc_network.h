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

typedef struct oc_message{
  int ID;
  char *name;
  int is_active;

  int read;
} oc_message;



void *oc_server(void *);


#endif /*OC_NETWORK*/
