#ifndef KRUSKAL_MST
#define KRUSKAL_MST

#include "deque.h"
#include "edgeGraph.h"
#include "generic_heap.h"
#include "union.h"



struct kruskalMST {

  struct Graph * graph;
  struct gheap * heap;
  struct Deque * deque;
  struct UF * uf;

};


struct kruskalMST * InitFilekMST(char * filename);

int edgeMin(struct gheap * heap, int i,int k);
void printEdgeHeap(struct gheap * heap);
void printEdge(struct node * edge);



#endif
