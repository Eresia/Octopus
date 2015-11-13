
//UDP server

#include "oc_network.h"
#include "../oc_kernel/oc_kernel.h"


extern object *root;


void err(char *str)
{
  perror(str);
  exit(1);
}

void *oc_server(void* empty)
{
  struct sockaddr_in my_addr, cli_addr;
  int sockfd;
  socklen_t slen=sizeof(cli_addr);
  char buf[BUFLEN];
  char *token1;
  char *token2;
  char *token3;
  int id = 0;

  if ((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))==-1)
    err("socket");
  else
    printf("Server : Socket() successful\n");

  bzero(&my_addr, sizeof(my_addr));
  my_addr.sin_family = AF_INET;
  my_addr.sin_port = htons(PORT);
  my_addr.sin_addr.s_addr = htonl(INADDR_ANY);

  if (bind(sockfd, (struct sockaddr* ) &my_addr, sizeof(my_addr))==-1)
    err("bind");
  else
    printf("Server : bind() successful\n");

  while(1)
    {
      if (recvfrom(sockfd, buf, BUFLEN, 0, (struct sockaddr*)&cli_addr, &slen)==-1)
	err("recvfrom()");
      printf("Received packet from %s:%d\nData: %s\n\n",
	     inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port), buf);


      token1 = strtok(buf,",");
      if (token1 != NULL) {
	token2 = strtok(NULL,",");
	if (token2 != NULL) {
	  token3 = strtok(NULL,",");
	  if (token3 != NULL) build_list(&root,atoi(token1), token2, atoi(token3));
	  else  fprintf(stderr,"message not recognized (third argument invalid)\n");
	}
	else fprintf(stderr,"message not recognized (second argument invalid)\n");
      }
      else fprintf(stderr,"message not recognized\n (fisrt argument invalid)");

    }

  close(sockfd);
  return 0;
}
