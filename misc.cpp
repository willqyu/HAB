#include <stdio.h>
#include "pico/stdlib.h"

#include "main.h"

void debug(const char * msg) {
    //Debugging
    if (DEBUG) {
        printf(msg);
    }
}

char Hex(char Character)
{
	char HexTable[] = "0123456789ABCDEF";
	
	return HexTable[Character];
}


