//UDPClient.c

#include "oc_network.h"

void err(char *s)
{
  perror(s);
  exit(1);
}

int main(int argc, char** argv)
{
  struct sockaddr_in serv_addr;
  int sockfd, slen=sizeof(serv_addr);
  char buf[BUFLEN];

  if(argc != 2)
    {
      printf("Usage : %s <Server-IP>\n",argv[0]);
      exit(0);
    }

  if ((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))==-1)
    err("socket");

  bzero(&serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(PORT);
  if (inet_aton(argv[1], &serv_addr.sin_addr)==0)
    {
      fprintf(stderr, "inet_aton() failed\n");
      exit(1);
    }

  while(1)
    {printf("message : ID,name,val1\n");
      printf("\nEnter data to send(Type exit and press enter to exit) : ");
      scanf("%[^\n]",buf);
      getchar();
      if(strcmp(buf,"exit") == 0)
	exit(0);

      if (sendto(sockfd, buf, BUFLEN, 0, (struct sockaddr*)&serv_addr, slen)==-1)
	err("sendto()");
    }

  close(sockfd);
  return 0;
}
