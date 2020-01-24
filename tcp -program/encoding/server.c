#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <ctype.h>
int main(int argc, char *argv[])
{
        int sockfd, newsockfd, portno,pp;
        int data[12],rdata[8];
        int r1,r2,r3,r4,m;
        socklen_t clilen;
        struct sockaddr_in serv_addr, cli_addr;
        int n,i,j;
        if(argc < 3)
        {
                fprintf(stderr,"Usage: %s <server IP>  <Server Port> \n",argv[0]);
                exit(1);
        }
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd < 0)
        {
                printf("ERROR opening socket");
                exit(1);
        }
        bzero((char *) &serv_addr, sizeof(serv_addr));
        serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
        portno = atoi(argv[2]);
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(portno);
        if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
        {
                printf("ERROR on binding");
                exit(1);
        }
        listen(sockfd,5);
        while(1)
        {
                printf(": waiting for connection request \n");
                clilen = sizeof(cli_addr);
                newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
                pp=fork();
                if(pp==0)
                {
                        close(sockfd);
                        printf("\n Connection request from a Client is accepted\n");

                        if (newsockfd < 0)
                          {
                                printf("ERROR on accept");
                                exit(1);
                        }
                        else
                        {

                 read(newsockfd,data,12*sizeof(int));
                r1=data[1]^data[3]^data[5]^data[7]^data[9]^data[11];
                r2=data[1]^data[2]^data[5]^data[6]^data[9]^data[10];
                r3=data[0]^data[5]^data[6]^data[7]^data[8];
                r4=data[0]^data[1]^data[2]^data[3]^data[4];
                m=r4*8+r3*4+r2*2+r1;
                if(m==0)
                        printf("no error\n");

                else
                {
                        printf("Error in position %d \n",12-m);
                printf("data received\n");
                for(i=0;i<12;i++)
                        printf("%d ",data[i]);
                printf("\n");
                if(data[12-m]==0)
                        data[12-m]=1;
                else
                        data[12-m]=0;

                }
         
                printf("Original data\n");
                for(i=0;i<12;i++)
                        printf("%d ",data[i]);

                                exit(4);
                        }
                               }
                                        else
                                        {
                                                wait(4);
                                                printf("\n");
                                                printf("closing connection with client\n");
                                                close(newsockfd);
                                        }
                                }
                                return 0;
                        }





