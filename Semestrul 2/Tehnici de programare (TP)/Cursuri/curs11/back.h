#ifndef __BACK_H__
#define __BACK_H__


#define MAX_STACK 100
#define MAX_PAYLOAD 10

typedef struct {
    int* payload;
    int (*succesor)(int*, int, int);
    int (*valid)(int*, int);
    int (*solutie)(int*, int, int*);
    void (*tipar)(int*, int);
}BackBehaviour_t;

void back(BackBehaviour_t behStruct);

#endif