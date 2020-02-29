/*
    Author: Muhammad Huzaifa Elahi
    ID: 260726386
*/
#ifndef PCB_H
#define PCB_H

typedef struct PCB_t {
    int PC;
    int start;
    int end;
} PCB;

PCB* makePCB(int start, int end);

#endif