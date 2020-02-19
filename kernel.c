#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "shell.h"
#include "pcb.h"
#include "ram.h"

PCB *head, *tail;

void addToReady(PCB *pcb);


int main(int argc, const char *argv[])
{
    shellUI();
}

int myinit(char *fileName){
    int start = 0;
    int end = 0;
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        printf("Script not found.\n");
        return 1;
    }
    int errCode = addToRAM(file, &start, &end);

    PCB* thisPCB = makePCB(start, end);
    addToReady(thisPCB);
}

void addToReady(PCB *pcb){

}

// TODO
//scheduler(){
//
// }


