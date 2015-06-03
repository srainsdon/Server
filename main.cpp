/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
//#include <sys/socket.h>
//#include <netinet/in.h>
#include <stdint.h>

using namespace std;

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

string bin(uint8_t n)
{
    int bob = n;
    cout << bob << endl;
    string ans;
    for (unsigned i = 1 << 7; i > 0; i = i / 2)
        (n & i)? ans =+ "1" : ans =+ "0";
    return ans;
}

void bin2(uint8_t n)
{
    for (unsigned i = 1 << 7; i > 0; i = i / 2)
        (n & i)? printf("1"): printf("0");
    printf(" = %u = %c\n", n, n);
}

int main(int argc, char *argv[])
{
    int sockfd, newsockfd, portno;
    char       buffer[256];
    memset(buffer, 0, 256);
    for(int i = 0; i < 64; i++) {
        uint8_t   *protoId = (uint8_t*)(buffer+i);
        *protoId = i;
    }
    for(int i = 0; i < 64; i++) {
        bin2(buffer[i]);
    }
    return 0;
}
