#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include<ctype.h>
int main(int argc, char *argv[])
{
        int sockfd, n;
        int data[12];
        int i,q,r,m;
        float p;
        struct sockaddr_in serv_addr;
        if(argc < 3)
        {
                fprintf(stderr,"Usage: %s <server IP>  <Server Port>\n",argv[0]);
                exit(1);
        }

/* build socket address data structure */

        bzero((char *) &serv_addr, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
        serv_addr.sin_port = htons(atoi(argv[2]));

  /* create socket, active open */
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if(sockfd<0)
        {
                printf("cannot open socket ");
                exit(1);
        }

  /* connect to server */
        if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
        {
                printf("ERROR connecting");
                exit(1);
        }

        printf("\n Connected to the server %s at TCP port %s\n",argv[1], argv[2]);

                  printf("Enter 8 bits of data one by one\n");
        scanf("%d",&data[0]);
        scanf("%d",&data[1]);
        scanf("%d",&data[2]);
            scanf("%d",&data[3]);
                scanf("%d",&data[5]);
                scanf("%d",&data[6]);
                scanf("%d",&data[7]);
                scanf("%d",&data[9]);
            //Calculation of even parity
            data[11]=data[1]^data[3]^data[5]^data[7]^data[9];
                data[10]=data[1]^data[2]^data[5]^data[6]^data[9];
                data[8]=data[0]^data[5]^data[6]^data[7];
                data[4]=data[0]^data[1]^data[2]^data[3];
                printf("\nEncoded data is\n");
                for(i=0;i<12;i++)
                printf("%d ",data[i]);
            printf("\n");
            printf("enter probability between 0 to 1\n");
                scanf("%f",&p);
                p=p*10;
            srand(time(0));
            q=rand()%10+1;
                printf("random no is :%d\n",q);
            if(q<p)
            {
                srand(time(0));
                r=rand()%12;
                printf("random position :%d\n",r);
                        if(data[r]==0)
                                data[r]=1;
                        else
                                data[r]=0;

                }
                write(sockfd,data,12*sizeof(int));

                close(sockfd);
                return 0;
        }

