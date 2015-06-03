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
    string ans;
    for (unsigned i = 1 << 7; i > 0; i = i / 2)
        (n & i)? ans =+ "1" : ans =+ "0";
    return ans;
}

int main(int argc, char *argv[])
{
    int sockfd, newsockfd, portno;
    char       buffer[256];
    memset(buffer, 0, 256);
    for(int i = 0; i < 4; i++) {
        uint8_t   *protoId = (uint8_t*)(buffer+i);
        *protoId = 255;
    }
    for(int i = 0; i < 8; i++) {
            string num = bin(buffer[i]);
            cout << num <<  buffer[i] << endl;
    }
    return 0;
}
