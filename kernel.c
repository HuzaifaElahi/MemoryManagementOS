#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "shell.h"
#include "pcb.h"
#include "ram.h"
#include "cpu.h"

struct QUEUE_NODE {
    PCB *thisPCB;
    struct QUEUE_NODE *next;
} *head = NULL, *tail = NULL;

void addToReady(PCB *pcb);

CPU* cpu;
char *ram[1000];

int main(int argc, const char *argv[])
{
    shellUI();
}

int myinit(char *fileName){
    int start = 0;
    int end = 0;
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        printf("exec: Script not found.\n");
        return 1;
    }
    int errCode = addToRAM(file, &start, &end);

    PCB* thisPCB = makePCB(start, end);
    addToReady(thisPCB);
    return errCode;
}

void addToReady(PCB *pcb){
    struct QUEUE_NODE *newPCB = malloc(sizeof(struct QUEUE_NODE));
    newPCB->thisPCB = pcb;

    if(head == NULL){
        head = newPCB;
        tail = newPCB;
    }else{
        tail->next = newPCB;
        tail = newPCB;
        tail->thisPCB = pcb;
    }
}

void scheduler(){
	struct QUEUE_NODE *oldhead;
    cpu = malloc(sizeof(CPU));
    cpu->quanta = 2;

    int index=0;
    while(head != NULL && head!=tail->next){
        PCB* removeHead = head->thisPCB;
        cpu->IP = removeHead->PC;
        oldhead = head;
        head = head->next;

        if(cpu->quanta < ((removeHead->end - removeHead->PC) + 1)){
            runCPU(cpu->quanta);
            removeHead->PC = cpu->IP;
            addToReady(removeHead);
        }else{
            runCPU((removeHead->end - removeHead->PC) + 1);

            for(int i = removeHead->start; i <= removeHead->end ; i++){
                ram[i] = NULL;
            }
            free(oldhead);
        }
        index++;
    }
    head = NULL;
}
