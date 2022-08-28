#include <stdio.h>
#include <string.h>
#include "slcan/slcan.h"

int main(int, char**) {
    printf("Hello, world from C application!\n");

    char line[32];
    strcpy(line, "S0\r");
    slcan_decode_line(line);
}
