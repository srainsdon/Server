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

    Message::Message(void *source)
    {
        buffer = source;
        uint8_t   *msgProt = (uint8_t*)(buffer);
        type = (int)*msgProt;
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
                (*(uint8_t*)(buffer+i) & j)? printf("1"): printf("0");
            }
            if(i!=byteCount-1)
                printf(":");
            if((i + 1) % 5 == 0)
                printf("\n");
        }
        printf("\n");
    }

    void Message::print_char()
    {
        int     stop    = 0;
        int     i       = 1;
        cout << "Message type: " << type << endl << "Message: ";
        while (stop < 2)
        {
            uint8_t   *msgProt = (uint8_t*)(buffer+i);
            cout << *msgProt;
            i++;
            if (*msgProt == 3 | *msgProt == 4)
            {
                ++stop;
            }
        }
    }
