#include "prim.h"

int edgeMin(struct gheap * heap, int i,int k){
  struct node * temp0 = (struct node * )(heap->array + i*sizeof(struct node));
  struct node * temp1 = (struct node * )(heap->array + k*sizeof(struct node));
  return temp0->weight > temp1->weight ? 1 : 0;
}

void printEdgeHeap(struct gheap * heap){

  int i;
  for(i=0; i<heapSize1(heap);i++){
    struct node * temp = (struct node * )(heap->array + i*heap->elementSize);
    printf("Src: %d\tDest: %d\tWeight: %lf\n",temp->src,temp->dest,temp->weight);
  }

}

void printEdge(struct node * temp){

  printf("Src: %d\tDest: %d\tWeight: %lf\n",temp->src,temp->dest,temp->weight);
  return;

}



struct primMST * InitFilekMST(char * filename){

  struct primMST * temp = (struct primMST *) malloc(sizeof(struct primMST));

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
  temp->deque = createDeque(sizeof(struct node));
  temp->marked = (int *) malloc(numVertices*sizeof(int));
  memset(temp->marked, 0x0, numVertices*sizeof(int));
  int v1 = 0;
  int v2 = 0;
  double w = 0.0;

  while(fscanf(file,"%d %d %lf\n",&v1,&v2,&w) != EOF){
    //printf("%d %d %f\n",v1,v2,w);

    addEdge(temp->graph,v1,v2,w);
    addEdge(temp->graph,v2,v1,w);

  }
  fclose(file);
  return temp;


}


void visit(struct primMST * prim, int v){

  prim->marked[v]=1;
  struct node * temp_edge =  adj(prim->graph, v);
  while (temp_edge){

    if(prim->marked[temp_edge->dest] != 1){
      //printEdge(temp_edge);
      //push_back(prim->deque,temp_edge);
      insertHeap(prim->heap,temp_edge);
    }
    temp_edge=temp_edge->next;
  }



  free(temp_edge);

}

int main(int argc, char ** argv){

  struct primMST * pmst = InitFilekMST(argv[1]);

  visit(pmst,0);
  printf("Heap size: %d\n", heapSize(pmst->heap));
  while(heapSize1(pmst->heap) != 0){

    printEdgeHeap(pmst->heap);
    printf("-----------------------------------\n");
    printf("Remove from Heap\t");
    struct node * edge = (struct node *)removeHeap(pmst->heap);
    printEdge(edge);
    printf("-----------------------------------\n");
    if(pmst->marked[edge->src]==1 && pmst->marked[edge->dest]==1) continue;
    printf("Add to mst\t");
    printEdge(edge);
    push_back(pmst->deque, edge);
    if(!pmst->marked[edge->src]) visit(pmst,edge->src);
    if(!pmst->marked[edge->dest]) visit(pmst,edge->dest);


  }


  return 0;
}
