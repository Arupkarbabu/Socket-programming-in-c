// Server program 
#include <arpa/inet.h> 
#include <errno.h> 
#include <netinet/in.h> 
#include <signal.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <strings.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <unistd.h>  
#define MAXLINE 1024 
int max(int x, int y) 
{ 
	if (x > y) 
		return x; 
	else
		return y; 
} 
int main(int argc ,char *argv[]) 
{ 
 if (argc != 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0] );
       exit(1);
    }
	int soocketfd, connfd, udpfd, nready, maxfdp1; 
	char buffer[MAXLINE]; 
	pid_t childpid; 
	fd_set rset; 
	ssize_t n; 
	socklen_t len; 
	int PORT;
	const int on = 1; 
	struct sockaddr_in cliaddr, servaddr; 
	char temp;
	void sig_chld(int); 
	PORT=atoi(argv[2]);
	int i,j;

	/* create listening TCP socket */
	soocketfd = socket(AF_INET, SOCK_STREAM, 0); 
	bzero(&servaddr, sizeof(servaddr)); 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
	servaddr.sin_port = htons(PORT); 
			if(inet_pton(AF_INET, argv[1], &servaddr.sin_addr)<=0)
					{
						printf("\n inet_pton error occured\n");
						return 1;
					}

	// binding server addr structure to soocketfd 
	bind(soocketfd, (struct sockaddr*)&servaddr, sizeof(servaddr)); 
	listen(soocketfd, 10); 

	/* create UDP socket */
	udpfd = socket(AF_INET, SOCK_DGRAM, 0); 
	// binding server addr structure to udp sockfd 
	bind(udpfd, (struct sockaddr*)&servaddr, sizeof(servaddr)); 

	// clear the descriptor set 
	FD_ZERO(&rset); 

	// get maxfd 
	maxfdp1 = max(soocketfd, udpfd) + 1; 
	for (;;) { 

							// set soocketfd and udpfd in readset 
FD_SET(soocketfd, &rset); 
FD_SET(udpfd, &rset); 
// select the ready descriptor 
nready = select(maxfdp1, &rset, NULL, NULL, NULL); 

// if tcp socket is readable then handle 
							// it by accepting the connection 
	if (FD_ISSET(soocketfd, &rset)) { 
len = sizeof(cliaddr); 
connfd = accept(soocketfd, (struct sockaddr*)&cliaddr, &len); 
if ((childpid = fork()) == 0) { 
	 close(soocketfd); 
		while(1){
	recv(connfd, buffer, 1024, 0);
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
send(connfd, buffer, strlen(buffer), 0);
printf("Disconnected from %s :%d\n", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));
printf("Client: %s\n", buffer); 
	close(connfd);
			exit(0);
			
													
	   }//if ke lia  
			
					}
								}
		                                                          
		// if udp socket is readable receive the message. 
 if (FD_ISSET(udpfd, &rset)) { 
      len = sizeof(cliaddr); 
     bzero(buffer, sizeof(buffer)); 
  while(1){
  recvfrom(udpfd, buffer, 1024, 0, (struct sockaddr*)&cliaddr , &len);
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
                     sendto(udpfd, buffer, 1024, 0, (struct sockaddr*)&cliaddr, sizeof(cliaddr));

                     printf("Disconnected from %s:%d\n", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));
                      printf("Client: %s\n", buffer);

                                        } 
	                                                    
														}
	
	
} 
return 0;
}
