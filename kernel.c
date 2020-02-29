/*
    Author: Muhammad Huzaifa Elahi
    ID: 260726386
*/
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
} *head = NULL, *tail = NULL, *oldhead;

void addToReady(PCB *pcb);

CPU* cpu;
char *ram[1000];

int main(int argc, const char *argv[])
{
    shellUI();
}

int myinit(char *fileName){
    // Load File
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        printf("exec: Script not found.\n");
        return 1;
    }
    // Populate Start, End instruction count values and add to RAM
    int start = 0, end = 0;
    int errCode = addToRAM(file, &start, &end);
    if(errCode != 0)	return errCode;

    // Create PCB and add to Ready Queue
    PCB* thisPCB = makePCB(start, end);
    addToReady(thisPCB);
    return errCode;
}

void addToReady(PCB *pcb){
    // Create Ready Queue Node for Program and add to List
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
    // Allocate memory for CPU
    cpu = malloc(sizeof(CPU));
    cpu->quanta = 2;
    int index=0;

    // Loop through ready queue
    while(head != NULL && head!=tail->next){

        // Remove Program and set CPU Instruction to it's Program Counter
        PCB* removeHead = head->thisPCB;
        cpu->IP = removeHead->PC;

        // Pick Minimum value between Quanta remaining and Program Instructions left
        if(cpu->quanta < ((removeHead->end - removeHead->PC) + 1)){
            runCPU(cpu->quanta);
            removeHead->PC = cpu->IP;
            addToReady(removeHead);
        }else{
            runCPU((removeHead->end - removeHead->PC) + 1);
            for(int i = removeHead->start; i <= removeHead->end ; i++){
                ram[i] = NULL;
            }
            free(oldhead); // Remove once all instructions are done
        }

        // Move head forwards
        index++;
        head = head->next;
    }
    // Reset HEAD and TAIL for Ready Queue
    head = NULL;
    tail = head;
}
