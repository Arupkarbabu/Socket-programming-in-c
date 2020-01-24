#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{

        int sockfd, ret;
    struct sockaddr_in serverAddr,cliaddr;
    int newSocket ,PORT;
        struct sockaddr_in newAddr;
    socklen_t addr_size;
    char buffer[1024],temp;
        int i,j;



 if (argc != 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0] );
       exit(1);
    }


        sockfd = socket(AF_INET, SOCK_DGRAM, 0);
        if(sockfd < 0){
                printf("[-]Error in connection.\n");
                exit(1);
        }

        printf("[+]Server Socket is created.\n");
       PORT=atoi(argv[2]);
        memset(&serverAddr, '\0', sizeof(serverAddr));
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(PORT);
        serverAddr.sin_addr.s_addr =INADDR_ANY;
		
		     if(inet_pton(AF_INET, argv[1], &serverAddr.sin_addr)<=0)
    {
        printf("\n inet_pton error occured\n");
        return 1;
    }



        ret = bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
        if(ret < 0){
                printf("[-]Error in binding.\n");
                exit(1);
        }
        printf("[+]Bind to port %d\n", PORT);

addr_size = sizeof(cliaddr);

                        while(1){
                          recvfrom(sockfd, buffer, 1024, 0, (struct sockaddr*)&cliaddr , &addr_size);
                                i = 0;
                                 j = strlen(buffer) - 1;
                                     while(i<j)
                                                 {
                                                temp = buffer[i];
                                                buffer[i] = buffer[j];
                                                 buffer[j] = temp;
                                                i++;
                                                j--;

                                                 }
                     sendto(sockfd, buffer, 1024, 0, (struct sockaddr*)&cliaddr, sizeof(cliaddr));

                     printf("Disconnected from %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));
                      printf("Client: %s\n", buffer);



                        }


        return 0;
        }

