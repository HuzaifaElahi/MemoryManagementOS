#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "ram.h"

// TODO: Error - Parses final line twice
// TODO: Error - Multiple Progs still don't work
int addToRAM(FILE *p, int *start, int *end){
    int currentLine = 0;
    char buffer[1000];
    while(!feof(p)){
        fgets(buffer, 1000, p);
        while(ram[currentLine] != NULL){
            currentLine++;
            *start = currentLine;
            if(currentLine == 1000){
                printf("exec: RAM overflow");
                return 1;
            }
        }
        ram[currentLine] = strdup(buffer);

        *end = currentLine;
        currentLine++;
        if(currentLine == 1000){
                printf("exec: RAM overflow");
                return 1;
        }
    }
    //*end = *end+1;

    return 0;
}
