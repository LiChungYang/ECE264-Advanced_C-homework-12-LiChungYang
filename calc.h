#ifndef _CALC_H_
#define _CALC_H_
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node{
    float val;
    struct Node * next;
}Node;

typedef struct Stack{
    Node * top;
}Stack;

Node * insert(float value, Node * list);
Node * delete(Node * list);
Stack * init();
bool isEmpty(Stack * st);
void push(Stack * st,float key);
float check(Stack * st);
float pop(Stack * st);
void freeStack(Stack * st);

#endif





