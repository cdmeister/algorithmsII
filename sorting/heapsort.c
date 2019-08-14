#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

// compile: gcc -I../data_struct/ ../data_struct/heap.c heapsort.c
void heapify(struct binary_heap * heap);
void heapsort(struct binary_heap * heap);


void heapsort(struct binary_heap * heap){

  heapify(heap);

  // We need to save off the iterator becuase sink()
  // uses the iterator when looping and we need to modify the
  // iterator so it points to the location we want for heapsort to work.
  int orig_iterator=heap->iterator;
  // Decrement the iterator since it points to one past the end so
  // now it points at the last element
  --heap->iterator;
  while(heap->iterator>0){
    // swap the root with the last element
    heap->swap(heap,heap->iterator,0);
    // decrement iterator
    --heap->iterator;
    // sink the root down the heap to proper location
    sink(heap,0);
  }
  // restore our iterator back to its former glory
  heap->iterator=orig_iterator;

}

void heapify(struct binary_heap * heap){

  // heap->iterator is already point one past the end so you need to subtract
  // 1 and then  another 1 because of 0 index heap.
  printf("it: %d\n",heap->iterator);
  int node = ((heap->iterator-1)/2)-1;

  while(node >=0){
    sink(heap,node);
    node--;
  }
}

int main(void){

  // Max heap
  struct  binary_heap *heap = initHeap(16,&heapMax);
  forcedInsertHeap(heap,9);
  forcedInsertHeap(heap,5);
  forcedInsertHeap(heap,12);
  forcedInsertHeap(heap,6);
  forcedInsertHeap(heap,3);
  forcedInsertHeap(heap,8);
  forcedInsertHeap(heap,15);
  forcedInsertHeap(heap,1);
  forcedInsertHeap(heap,4);
  forcedInsertHeap(heap,2);
  forcedInsertHeap(heap,7);
  forcedInsertHeap(heap,10);
  forcedInsertHeap(heap,11);
  forcedInsertHeap(heap,13);
  forcedInsertHeap(heap,16);
  forcedInsertHeap(heap,0);
  printHeap(heap);
  heapsort(heap);
  printHeap(heap);


  return 0;
}

