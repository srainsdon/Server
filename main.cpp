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

#define BUFF_SZ 256

int main(int argc, char *argv[])
{
    char       buffer[BUFF_SZ];
    memset(buffer, 0, BUFF_SZ);
    Message msg(buffer);
    Message msg2("This is a test");
    msg.print_bin(40*8);
    msg.print_char();
    return 0;
}
