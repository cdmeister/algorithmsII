#include "kruskal.h"

int edgeMin(struct gheap * heap, int i,int k){
  struct node * temp0 = (struct node * )(heap->array + i*sizeof(struct node));
  struct node * temp1 = (struct node * )(heap->array + k*sizeof(struct node));
  return temp0->weight > temp1->weight ? 1 : 0;
}

void printEdgeHeap(struct gheap * heap){

  int i;
  for(i=0; i<heap->iterator;i++){
    struct node * temp = (struct node * )(heap->array + i*heap->elementSize);
    printf("Src: %d\tDest: %d\tWeight: %lf\n",temp->src,temp->dest,temp->weight);
  }

}

void printEdge(struct node * temp){

  printf("Src: %d\tDest: %d\tWeight: %lf\n",temp->src,temp->dest,temp->weight);
  return;

}



struct kruskalMST * InitFilekMST(char * filename){

  struct kruskalMST * temp = (struct kruskalMST *) malloc(sizeof(struct kruskalMST));

  FILE * file = fopen(filename,"r");
  if(file == NULL)
  {
    printf("Error!\n");
    exit(1);
  }

  int numVertices = 0;
  int numEdges = 0;
  double weight = 0.0;

  fscanf(file,"%d\n",&numVertices);
  fscanf(file,"%d\n",&numEdges);
  printf("NumVerticeis: %d NumEdges: %d\n",numVertices,numEdges);
  temp->heap  =  initHeap(numEdges,sizeof(struct node),&edgeMin);
  temp->graph =  InitEmptyGraph(numVertices,numEdges);
  temp->uf = createUnion(numVertices);
  temp->deque = createDeque(sizeof(struct node));

  int v1 = 0;
  int v2 = 0;
  double w = 0.0;
  struct node * temp_edge = (struct node *) malloc(sizeof(struct node));
  while(fscanf(file,"%d %d %lf\n",&v1,&v2,&w) != EOF){
    printf("%d %d %f\n",v1,v2,w);
    temp_edge->src = v1;
    temp_edge->dest = v2;
    temp_edge->weight = w;
    insertHeap(temp->heap, temp_edge);

    addEdge(temp->graph,v1,v2,w);
    addEdge(temp->graph,v2,v1,w);

  }
  free(temp_edge);
  fclose(file);
  return temp;


}

int main(int argc, char ** argv){

  struct kruskalMST * kmst = InitFilekMST(argv[1]);

  printEdgeHeap(kmst->heap);

  while(heapSize(kmst->heap) != 0 && sizeDeque(kmst->deque)<V(kmst->graph)-1){

    struct node * edge = (struct node *)removeHeap(kmst->heap);
    if(unionConnected(kmst->uf, edge->src, edge->dest)) continue;
    unionUnion(kmst->uf,edge->src,edge->dest);
    push_back(kmst->deque,edge);
    printf("Hello\n");
    printEdge(edge);
  }

  return 0;
}
