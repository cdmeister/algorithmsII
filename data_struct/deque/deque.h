#ifndef DEQUE_H
#define DEQUE_H

#include "stdio.h"
#include "stdlib.h"


struct dequeNode{
  void * data;
  struct dequeNode * next;
  struct dequeNode * prev;
};

struct Deque{
  struct dequeNode * head;
  struct dequeNode * tail;
};


struct Deque * createDeque();

void push_front(struct Deque * deque, void * data);
void *  pop_front(struct Deque * deque);


void push_back(struct Deque * deque, void * data);
void *  pop_back(struct Deque * deque);

void printDeque(struct Deque * deque);

int isEmpty(struct Deque * deque);
#endif
