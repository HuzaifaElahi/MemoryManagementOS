/*
    Author: Muhammad Huzaifa Elahi
    ID: 260726386
*/
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "ram.h"

int addToRAM(FILE *p, int *start, int *end){
    int currentLine = 0;
    char buffer[1000];

    // Add Lines from File into RAM & Ensure Overflow is avoided
    while(!feof(p)){
        char *line = NULL;
        size_t linecap = 0;
        getline(&line, &linecap, p);

        while(ram[currentLine] != NULL){
            currentLine++;
            *start = currentLine;
            if(currentLine == 1000){
                printf("exec: RAM overflow");
                return 1;
            }
        }
        ram[currentLine] = strdup(line);

        *end = currentLine;
        currentLine++;
        if(currentLine == 1000){
                printf("exec: RAM overflow");
                return 1;
        }
    }

    return 0;
}
