/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdint.h>

using namespace std;

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

void bin(uint8_t n)
{
    for (unsigned i = 1 << 7; i > 0; i = i / 2)
        (n & i)? printf("1"): printf("0");
    printf("\n");
}

int main(int argc, char *argv[])
{
    int sockfd, newsockfd, portno;
    socklen_t clilen;
    char       buffer[256];
    for(int i = 0; i < 256; i++) {
        if(i%4 == 0) {
            printf("uint %d = %u\n", i / 4, *(uint32_t*)(buffer+i));
        }
        bin(buffer[i]);
    }
    memset(buffer, 0, 256);
    uint32_t   *protoId = (uint32_t*)(buffer);
    uint32_t   *protoId2 = (uint32_t*)(buffer+4);
    *protoId2 = 300;
    *protoId = 999999;
    /*printf("uint 0\n");
    bin(buffer[0]);
    bin(buffer[1]);
    bin(buffer[2]);
    bin(buffer[3]);
    printf("uint 1\n");
    bin(buffer[4]);
    bin(buffer[5]);
    bin(buffer[6]);
    bin(buffer[7]);
    printf("uint n\n");
    bin(buffer[8]);*/
    struct sockaddr_in serv_addr, cli_addr;
    int n;
    if (argc < 2)
    {
        fprintf(stderr,"ERROR, no port provided\n");
        exit(1);
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    if (bind(sockfd, (struct sockaddr *) &serv_addr,
             sizeof(serv_addr)) < 0)
        error("ERROR on binding");
    listen(sockfd,5);
    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd,
                       (struct sockaddr *) &cli_addr,
                       &clilen);
    if (newsockfd < 0)
        error("ERROR on accept");
    bzero(buffer,256);
    n = read(newsockfd,buffer,255);
    if (n < 0) error("ERROR reading from socket");
    //std::string msgType = str.copy(buffer,0,3);
    printf("Here is the message: %s\n",buffer);
//    cout << "Message Type: " << msgType << endl;
    n = write(newsockfd,"I got your message",18);
    if (n < 0) error("ERROR writing to socket");
    close(newsockfd);
    close(sockfd);
    return 0;
}
