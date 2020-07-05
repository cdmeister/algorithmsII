#ifndef PRIM_MST
#define PRIM_MST

#include "deque.h"
#include "edgeGraph.h"
#include "generic_heap.h"
#include "union.h"



struct primMST {

  struct Graph * graph;
  struct gheap * heap;
  struct Deque * deque;
  int * marked;

};


struct primMST * InitFilekMST(char * filename);

int edgeMin(struct gheap * heap, int i,int k);
void printEdgeHeap(struct gheap * heap);
void printEdge(struct node * edge);



#endif
