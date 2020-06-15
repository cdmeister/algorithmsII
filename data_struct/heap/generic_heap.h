#ifndef __HEAP_H
#define __HEAP_H
#include "stdlib.h"
#include "string.h"

struct gheap{
  void * array;
  int num;
  size_t size;
  int iterator;
  int (*comparator)(struct gheap *,int i ,int k);
};

struct gheap * initHeap(int count, size_t size,
                        int (*comparator)(struct gheap *,int i,int k));


void sink(struct gheap * heap, int k);
void swim(struct gheap * heap, int k);
void insertHeap(struct gheap * heap, const void * data);
void forcedInsertHeap(struct gheap * heap, const void * data);
void * removeHeap(struct gheap * heap);
void * getPtr(struct gheap * heap, int i);

#endif
