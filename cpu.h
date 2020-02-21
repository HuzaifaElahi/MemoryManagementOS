#ifndef CPU_H
#define CPU_H

void runCPU(int);

typedef struct CPU_t {
    int IP;
    char IR[1000];
    int quanta;
} CPU;

extern CPU *cpu;

#endif