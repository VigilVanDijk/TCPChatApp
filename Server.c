#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

void error(const char *msg)
{
        perror(msg);
        exit(1);
}

int main(int argc, char *argv[])
{
        if(argc<2)
                {
                        printf("Port no not provided\n");
                }
        int sockfd, newsockfd, portno, n;
        char buffer[255];
        struct sockaddr_in serv_addr, client_addr;
        socklen_t clilen;
        sockfd=socket(AF_INET, SOCK_STREAM, 0);
        if(sockfd < 0)
        {
        printf("socket not created");
        }
        bzero((char*)&serv_addr, sizeof(serv_addr));
        portno=atoi(argv[1]);
        serv_addr.sin_family=AF_INET;
        serv_addr.sin_addr.s_addr=INADDR_ANY;
        serv_addr.sin_port=htons(portno);
        if(bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr))<0)
        {
        printf("Bind Failed");
        }
        listen(sockfd, 5);
        clilen=sizeof(client_addr);
        newsockfd=accept(sockfd, (struct sockaddr *)&client_addr, &clilen);
        if(newsockfd<0)
        {
        printf("Not accepted");
        }
        while(1)
        {
        bzero(buffer, 255);
        n=read(newsockfd, buffer, 255);
        if(n<0)
        {
        printf("Reading error");
        }
        else
        {
        printf("Client : %s \n", buffer);
        }
        bzero(buffer, 255);
        fgets(buffer, 255, stdin);
        n= write(newsockfd, buffer, strlen(buffer));
        if(n<0)
        {
        printf("Error whiile writitng");
        }
        int i= strncmp("bye", buffer, 3);
        if(i==0)
        {
        break;
        }
        }

close(newsockfd);
close(sockfd);
return 0;
}




