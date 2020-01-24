#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>



int main(int argc, char *argv[])
{

        int clientSocket, ret;
        struct sockaddr_in serverAddr;
        char buffer[1024];
        int PORT;
        PORT = atoi(argv[2]);


        if(argc != 4)
    {
        printf("\n Usage: %s <ip of server> \n",argv[0]);
        return 1;
    }
clientSocket = socket(AF_INET, SOCK_STREAM, 0);
        if(clientSocket < 0){
                printf("[-]Error in connection.\n");
                exit(1);
        }
        printf("[+]Client Socket is created.\n");

         memset(&serverAddr, '\0', sizeof(serverAddr));
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(PORT);

          if(inet_pton(AF_INET, argv[1], &serverAddr.sin_addr)<=0)
    {
        printf("\n inet_pton error occured\n");
        return 1;
    }
	  ret = connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
        if(ret < 0){
                printf("[-]Error in connection.\n");
                exit(1);
        }
        printf("[+]Connected to Server.\n");

        while(1){

                strcpy(buffer, argv[3]);
                send(clientSocket, buffer, strlen(buffer), 0);
                printf("[-]Disconnected from server.\n");
                recv(clientSocket, buffer, 1024, 0);
                printf("Server: %s\n ", buffer);
                close(clientSocket);
                break;
        }


        return 0;
}