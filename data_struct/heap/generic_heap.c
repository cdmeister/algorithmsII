#include <stdio.h>
#include <stdlib.h>
#include "generic_heap.h"

// Useful SO post about using 0 index heap and its formula
// https://stackoverflow.com/questions/22900388/why-in-a-heap-implemented-by-array-the-index-0-is-left-unused

struct gheap * initHeap(int count, size_t size,
                        int (*comparator)(struct gheap *,int i, int k)){

  struct  gheap *heap = malloc(sizeof(struct gheap));
  heap->capacity = count;
  heap->elementSize = size;
  heap->num = 0;
  heap->iterator = 0;
  heap->array = calloc(heap->capacity,heap->elementSize);
  heap->comparator = comparator;

  return heap;
}

void swap(void *vp1,void *vp2,int size)
{
  char buf[size];
  memcpy(buf,vp1,size);
  memcpy(vp1,vp2,size);
  memcpy(vp2,buf,size);  //memcpy ->inbuilt function in std-c
}



void * getPtr(struct gheap * heap, int i){

  return (void *) (heap->array + (i*heap->elementSize));
}

void sink(struct gheap * heap, int k){
  while(2*k+1 < heap->iterator){
    int j = 2*k+1; //Left child

    // compare which child is greater
    if(heap->comparator(heap,j,j+1) && j+1<heap->iterator) j++;

    // if the child j is less than the parent then we done sinking
    // which means the parent is greater than both children
    if(!heap->comparator(heap,k,j)) break;

    // Swap
    swap(getPtr(heap,k), getPtr(heap,j), heap->elementSize);

    // set the new parent to the child you just swapped with
    k = j;
  }
}

void swim(struct gheap * heap, int k){
  // if the parent node k/2 is less than child node k
  // then swap
  while(heap->comparator(heap,(k-1)/2,k)&k>0){
    swap(getPtr(heap,(k-1)/2), getPtr(heap,k), heap->elementSize);
    k=(k-1)/2;
  }
}

void insertHeap(struct gheap * heap, const void * data){
  //printf("inserting ");
  void * dest = heap->array+(heap->elementSize*heap->iterator);
  memcpy(dest, data, heap->elementSize);
  swim(heap,heap->iterator);
  heap->iterator++;
  heap->num++;

}


// Just insert into array and do not call swim.
// Primarily to demonstrate heapsort
void forcedInsertHeap(struct gheap * heap, const void * data){
  void * dest = heap->array+(heap->elementSize*heap->iterator);
  memcpy(dest, data, heap->elementSize);
  heap->iterator++;
  heap->num++;

}

void * removeHeap(struct gheap * heap){
  void * root = getPtr(heap,0);
  void * end = getPtr(heap, --heap->iterator);
  swap(root,end,heap->elementSize);
  //printf("calling sink in removeHeap\n");
  sink(heap,0);
  heap->num--;
  return end;
}

int heapSize(struct gheap * heap){

  return heap->iterator;

}

int heapSize1(struct gheap * heap){

  return heap->num;

}

