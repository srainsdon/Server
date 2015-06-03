#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdint.h>
#include <cmath>
#include "message.h"
using namespace std;

#define BUFF_SZ 1024


void sendMessage(void *source, string msgText, int msgT = 255)
{
    int     msgLng = msgText.length();
    int l = 0;
    for(int i = 0; i < 1+msgLng; i++)
    {
        uint8_t   *msgTxt = (uint8_t*)(source+i);
        switch ( i )
        {

        case 0 :
            *msgTxt = msgT;
            break;

        case 1 :
            *msgTxt = 2; // Start of text
            break;

        default :
            char c = msgText[l];
            *msgTxt = (uint8_t)c;
            l++;
        }
    }
    uint16_t   *msgEnd = (uint16_t*)(source+1+msgLng);
    *msgEnd = 1027; // sets final bites to 3 and 4
}

int main(int argc, char *argv[])
{
    char       buffer[256];
    memset(buffer, 0, 256);
    sendMessage(buffer, "Testing message sending functions", 170);
    Message msg(buffer);
    msg.print_bin(40*8);
    msg.print_char();
    return 0;
}
