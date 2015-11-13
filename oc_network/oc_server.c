
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
    char size[2];
    char* typeOfMessage;
    Data data;
    char *temp, *string;
    int generalId = 0;
    int dataSize;

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
        if(recvfrom(sockfd, size, 2, 0, (struct sockaddr*)&cli_addr, &slen)==-1)
        err("recvfrom() size");
        dataSize = atoi(size);
        if(dataSize != 0){
            if (recvfrom(sockfd, buf, BUFLEN, 0, (struct sockaddr*)&cli_addr, &slen)==-1)
            err("recvfrom() data");
            printf("Received packet from %s:%d\nData: %s\n\n",
            inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port), buf);

            typeOfMessage = strtok(buf, ",");
            if(typeOfMessage != NULL){
                if(strcmp(typeOfMessage, NEW_CONNEXION)){

                }
                else if(strcmp(typeOfMessage, DATA)){
                    data.id = strtok(buf,",");
                    if (data.id != NULL) {
                        temp = strtok(NULL,",");
                        if (temp != NULL) {
                            string = whichData(data, temp);
                            temp = strtok(NULL,",");
                            if ((temp != NULL) && (string != NULL)){
                                


                                printf("Client %d", atoi(data.id));
                                build_list(&root,atoi(tokens[0]), tokens[1], atoi(tokens[2]));
                            }
                            else  fprintf(stderr,"message not recognized (third argument invalid)\n");
                        }
                        else fprintf(stderr,"message not recognized (second argument invalid)\n");
                    }
                    else fprintf(stderr,"message not recognized\n (fisrt argument invalid)");
                }
                else{
                    fprintf(stderr,"Bad type of data\n");
                }
            }
        }
        else fprintf(stderr,"Bad size of data");

    }

    close(sockfd);
    return 0;
}

char* whichData(Data data, char* string){
    if(strcmp(string, PAN) == 0){
        return data.pan;
    }
    else if(strcmp(string, TILT) == 0){
        return data.tilt;
    }
    else{
        return NULL;
    }
}
