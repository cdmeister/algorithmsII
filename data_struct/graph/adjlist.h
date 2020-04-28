#ifndef ADJLIST_H
#define ADJLIST_H

struct node {
  int vertex;
  struct node * next;
};

struct graph {
  int numVertices;
  int numEdges;
  struct node ** adjlist;
};



#endif /* ADJLIST_H */
