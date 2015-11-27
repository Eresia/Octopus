
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
    Data data;
    char *allData, **separate;
    int generalId = 0;

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
        err("recvfrom() data");
        printf("Received packet from %s:%d\nData: %s -\n\n",
        inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port), buf);

        separate = dividedString(buf, 3);

        if(strcmp(separate[0], NEW_CONNEXION) == 0){
            #ifdef DEBUG
            printf("New connexion\n");
            #endif
            char* idString = malloc(2*sizeof(char));
            if(generalId < 10)
                sprintf(idString, "0%d", generalId);
            else
                sprintf(idString, "%d", generalId);
            sendto(sockfd, idString, 2, 0, (struct sockaddr*)&cli_addr, sizeof(cli_addr));
            generalId++;
        }
        else if(strcmp(separate[0], DATA) == 0){
            #ifdef DEBUG
                printf("New message\n");
            #endif
            data.id = strtok(separate[1],",");
            if (data.id != NULL) {
                allData = strtok(NULL,"-");
                /*do{
                    if (temp != NULL) {
                        string = whichData(data, temp);
                        temp = strtok(NULL,",");
                        if ((temp != NULL) && (string != NULL)){
                            if(atoi(temp) != 0)
                            *string = temp;
                        }
                    }
                    temp = strtok(NULL,",");
                } while(temp != NULL);*/
                if(allData != NULL){
                    #ifdef DEBUG
                    printf("Client %d envoie %s\n", atoi(data.id), allData);
                    #endif
                    build_list(&root,atoi(data.id), allData, 1024);
                    sendto(sockfd, "ok", 2, 0, (struct sockaddr*)&cli_addr, sizeof(cli_addr));
                }
                else{
                    printf("No Data\n");
                }
            }
            else{
                printf("No ID\n");
            }
        }
        else{
            printf("Bad type of data\n");
        }

    }

    close(sockfd);
    return 0;
}

char** whichData(Data data, char* string){
    char** result = NULL;
    if(strcmp(string, PAN) == 0){
        result = &(data.pan);
    }
    else if(strcmp(string, TILT) == 0){
        result = &(data.tilt);
    }
    return result;
}

char** dividedString(char* string, int nbChar){
    int i = 0;
    char** result = (char**) malloc(2*sizeof(char*));
    result[0] = (char*) malloc(nbChar*sizeof(char));
    result[1] = (char*) malloc((strlen(string) - nbChar)*sizeof(char));

    for(i = 0; i < strlen(string); i++){
        if(i < nbChar)
        result[0][i] = string[i];
        else
        result[1][i-nbChar] = string[i];
    }

    return result;
}
