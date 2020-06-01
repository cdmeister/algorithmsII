#ifndef EDGEWEIGHTGRAPH_H
#define EDGEWEIGHTGRAPH_H

#include "stdio.h"
#include "stdlib.h"

struct node {
  int src,dest;
  double weight;
  struct node * next;
};

struct Graph {
  int numVertices;
  int numEdges;
  struct node ** adjlist;
  int * visited;
};


struct Graph * InitEmptyGraph(int numVertices, int numEdges);
struct Graph * InitFileGraph(char * filename);

int V(struct Graph * graph);
int E(struct Graph * graph);

void addEdge(struct Graph * graph, int v, int w, double weight);
struct node * adj(struct Graph * graph, int v);

char * toString(struct Graph * graph);
void printGraph(struct Graph * graph);

struct node * createNode(int src, int dest, double weight);
#endif /* EDGEWEIGHTGRAPH_H */
