#ifndef __HEAP_H
#define __HEAP_H

struct binary_heap{
  int * array;
  int num;
  int iterator;
  int (*comparator)(struct binary_heap *,int,int);
  void (*swap)(struct binary_heap *,int,int);
};


void printHeap(struct binary_heap * heap);
void swap(struct binary_heap * heap, int node1, int node2);
int heapMax(struct binary_heap * heap,int node1,int node2 );
int heapMin(struct binary_heap * heap,int node1,int node2 );
void sink(struct binary_heap * heap, int k);
void swim(struct binary_heap * heap, int k);
void insertHeap(struct binary_heap * heap, int k);
void forcedInsertHeap(struct binary_heap * heap, int k);
int removeHeap(struct binary_heap * heap);
struct binary_heap * initHeap(int size, int (*comparator)(struct binary_heap *,int,int));
void printHeap(struct binary_heap * heap);
void printFullHeap(struct binary_heap * heap);

#endif
