#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

// Useful SO post about using 0 index heap and its formula
// https://stackoverflow.com/questions/22900388/why-in-a-heap-implemented-by-array-the-index-0-is-left-unused

void swap(struct binary_heap * heap, int node1, int node2){

  printf("swapping %d with %d\n",heap->array[node1], heap->array[node2]);
  int temp = heap->array[node1];
  heap->array[node1]= heap->array[node2];
  heap->array[node2] = temp;
  return;
}

int heapMax(struct binary_heap * heap,int node1,int node2 ){
return heap->array[node1]<heap->array[node2] ? 1 : 0;
}


int heapMin(struct binary_heap * heap,int node1,int node2 ){
return heap->array[node1]>heap->array[node2] ? 1 : 0;
}


void sink(struct binary_heap * heap, int k){
  while(2*k+1 < heap->iterator){
    int j = 2*k+1; //Left child

    // compare which child is greater
    if(heap->comparator(heap,j,j+1) && j<heap->iterator) j++;

    // if the child j is less than the parent then we done sinking
    // which means the parent is greater than both children
    if(!heap->comparator(heap,k,j)) break;

    // Swap
    heap->swap(heap, k, j);

    // set the new parent to the child you just swapped with
    k = j;
  }
}

void swim(struct binary_heap * heap, int k){
  // if the parent node k/2 is less than child node k
  // then swap
  while(heap->comparator(heap,(k-1)/2,k)&k>0){
    heap->swap(heap,(k-1)/2,k);
    k=(k-1)/2;
  }
}

void insertHeap(struct binary_heap * heap, int k){
  printf("inserting %d\n",k);
  heap->array[heap->iterator]=k;
  swim(heap,heap->iterator);
  heap->iterator++;

}

// Just insert into array and do not call swim.
// Primarily to demonstrate heapsort
void forcedInsertHeap(struct binary_heap * heap, int k){
  printf("inserting %d\n",k);
  heap->array[heap->iterator]=k;
  heap->iterator++;

}

int removeHeap(struct binary_heap * heap){
  int root = heap->array[0];
  heap->swap(heap,0,--heap->iterator);
  printf("calling sink in removeHeap\n");
  sink(heap,0);
return root;
}

struct binary_heap * initHeap(int size, int (*comparator)(struct binary_heap *,int,int)){

  struct  binary_heap *heap = malloc(sizeof(struct binary_heap));
  heap->num = size;
  heap->iterator = 0;
  heap->array = calloc(heap->num,sizeof(int));
  heap->comparator = comparator;
  heap->swap = &swap;

  return heap;
}

void printHeap(struct binary_heap * heap){

   int i;
   for(i=0;i<heap->iterator;i++){
     printf("%d\t",heap->array[i]);
   }
   printf("\n");

}

void printFullHeap(struct binary_heap * heap){

   int i;
   for(i=0;i<heap->num;i++){
     printf("%d\t",heap->array[i]);
   }
   printf("\n");

}

/*
int main(void){

  // Max heap
  struct  binary_heap *heap1 = initHeap(16,&heapMax);
  insertHeap(heap1,9);
  insertHeap(heap1,5);
  insertHeap(heap1,12);
  insertHeap(heap1,6);
  insertHeap(heap1,3);
  insertHeap(heap1,8);
  insertHeap(heap1,15);
  insertHeap(heap1,1);
  insertHeap(heap1,4);
  insertHeap(heap1,2);
  insertHeap(heap1,7);
  insertHeap(heap1,10);
  insertHeap(heap1,11);
  insertHeap(heap1,13);
  insertHeap(heap1,16);
  insertHeap(heap1,0);
  printHeap(heap1);
  int root = removeHeap(heap1);
  printf("root: %d\n",root);
  printHeap(heap1);

  // Min heap
  struct  binary_heap *heap2 = initHeap(16,&heapMin);
  insertHeap(heap2,9);
  insertHeap(heap2,5);
  insertHeap(heap2,12);
  insertHeap(heap2,6);
  insertHeap(heap2,3);
  insertHeap(heap2,8);
  insertHeap(heap2,15);
  insertHeap(heap2,1);
  insertHeap(heap2,4);
  insertHeap(heap2,2);
  insertHeap(heap2,7);
  insertHeap(heap2,10);
  insertHeap(heap2,11);
  insertHeap(heap2,13);
  insertHeap(heap2,16);
  insertHeap(heap2,0);
  printHeap(heap2);
  root = removeHeap(heap2);
  printf("root: %d\n",root);
  printHeap(heap2);


  return 0;
}
*/
