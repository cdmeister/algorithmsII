#include "deque.h"
#include "edgeGraph.h"
#include "generic_heap.h"
#include "union.h"



struct kruskalMST {

  struct Graph * graph;
  struct gheap * minHeap;
  struct Deque * deque;
  struct UF * uf;

};


struct kruskalMST * InitFilekMST(char * filename);

int edgeMin(struct gheap * heap, int i,int k);
void printEdgeHeap(struct gheap * heap);
void printEdge(struct node * edge);

