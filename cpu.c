/*
    Author: Muhammad Huzaifa Elahi
    ID: 260726386
*/
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "cpu.h"
#include "interpreter.h"
#include "ram.h"

void runCPU(int quanta){
    // Fetch and execute instructions while quanta is given
    while(quanta > 0){
        strcpy(cpu->IR, ram[cpu->IP]);
        interpret(cpu->IR);
        cpu->IP++;
        quanta--;
    }
}