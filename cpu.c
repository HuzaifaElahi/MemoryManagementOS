#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

struct CPU {
    int IP;
    char IR[1000];
    int quanta: 2;
};

