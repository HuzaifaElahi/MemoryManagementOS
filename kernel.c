#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "shell.h"
#include "pcb.h"
#include "ram.h"

struct QUEUE_NODE {
    PCB *thisPCB;
    struct QUEUE_NODE *next;
} *head = NULL, *tail = NULL;

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
    struct QUEUE_NODE *newPCB = malloc(sizeof(struct QUEUE_NODE));
    newPCB->thisPCB = pcb;

    if(head == NULL){
        head = newPCB;
        tail = newPCB;
    }else{
        tail->next = newPCB;
        tail->thisPCB = pcb;
    }
}

// TODO
// scheduler(){
//
// }


