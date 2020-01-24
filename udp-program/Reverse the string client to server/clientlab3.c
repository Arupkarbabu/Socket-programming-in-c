#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>



int main(int argc, char *argv[])
{

    if(argc != 4)
    {
        printf("\n Usage: %s <ip of server> \n",argv[0]);
        return 1;
    }
        int sockfd, ret;
        struct sockaddr_in serverAddr,si_other;
        char buffer[1024];
        int PORT;
        PORT = atoi(argv[2]);



sockfd = socket(PF_INET, SOCK_DGRAM, 0);
        if(sockfd < 0){
            printf("[-]Error in connection.\n");
            exit(1);
        }
printf("[+]Client Socket is created.\n");

        memset(&serverAddr, '\0', sizeof(serverAddr));
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(PORT);
                serverAddr.sin_addr.s_addr = INADDR_ANY;

      if(inet_pton(AF_INET, argv[1], &serverAddr.sin_addr)<=0)
    {
        printf("\n inet_pton error occured\n");
        return 1;
    }
       socklen_t addr_size;
	   
	     addr_size = sizeof(si_other);

        while(1){
                printf("[+]Connecting to Server.\n");
                strcpy(buffer, argv[3]);

                sendto(sockfd, buffer, 1024, 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));

                recvfrom(sockfd, buffer, 1024, 0, (struct sockaddr*)&si_other, &addr_size);
                printf("[+]Data Received:\n");

                printf("Server: %s\n ", buffer);
                close(sockfd);
                break;

                  }


        return 0;
}
	   
	   
	   
	   
	   