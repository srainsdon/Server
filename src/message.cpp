#include "message.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdint.h>
#include <cmath>
using namespace std;

/***********************************************************
void Message::print_char() && void Message::print_bin(unsigned hBit)
Testing functions that need to be moved over to a testing
class. I just don't know how to make sure it is working with
this classes buffer. (I might have just though of it pass it
the buffer from this class to that class.
***********************************************************/

void Message::print_char()
{
    int     stop    = 0;
    int     i       = 1;
    cout << "Message type: " << type << endl << "Message: ";
    while (stop < 2)
    {
        char   *msgChar = (char*)((uint8_t*)buffer+i);
        cout << *msgChar;
        i++;
        if (*msgChar == 3 | *msgChar == 4)
        {
            ++stop;
        }
    }
}

//this function require math.h to be included for c or cmath if using c++
void Message::print_bin(unsigned hBit)
{
    unsigned byteCount = ceil(hBit/8.0);
    unsigned byteRemain= hBit%8;
    for(int i = 0; i < byteCount; i++)
    {
        uint8_t j = (i==byteCount-1) ? (1 << byteRemain) : (1 << 7);
        for(uint8_t j = 1 << 7; j > 0; j/=2)
        {
            (*(uint8_t*)(((uint8_t*)buffer)+i) & j)? printf("1"): printf("0");
        }
        if(i!=byteCount-1)
            printf(":");
        if((i + 1) % 5 == 0)
            printf("\n");
    }
    printf("\n");
}

/***********************************************************
void setMessage(void *source, string msgText, int msgT)
Sets the buffer up so that it can be sent
***********************************************************/

void setMessage(void *source, string msgText, int msgT = 255)
{
    int     msgLng = msgText.length();
    int l = 0;
    for(int i = 0; i < 2+msgLng; i++)
    {
        uint8_t   *msgTxt = (uint8_t*)(((uint8_t*)source)+i);
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
    uint16_t   *msgEnd = (uint16_t*)(((uint8_t*)source)+2+msgLng);
    *msgEnd = 1027; // sets final bites to 3 and 4
}

/***********************************************************
Message::Message(void *source)
initializing class with a void pointer sets up for receiving
***********************************************************/

Message::Message(void *source)
{
    buffer = source;
    uint8_t   *msgProt = (uint8_t*)(buffer);
    type = (int)*msgProt;
}

/***********************************************************
Message::Message(string msgString, int msgT)
initializing class with a string sets up for sending
***********************************************************/

Message::Message(string msgString, int msgT)
{
    char    source[256];
    //setMessage(source, msgString, msgT);
}
