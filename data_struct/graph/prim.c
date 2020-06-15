#include "prim.c"


int edgeMin(struct gheap * heap, int i,int k){
  struct edge * temp0 = (struct edge * )(heap->array + i*sizeof(struct edge));
  struct edge * temp1 = (struct edge * )(heap->array + k*sizeof(struct edge));
  return temp0->weight > temp1->weight ? 1 : 0;
}

void printEdgeHeap(struct gheap * heap){

  int i;
  for(i=0; i<heap->num;i++){
    struct edge * temp = (struct edge * )(heap->array + i*heap->size);
    printf("Src: %d\tDest: %d\tWeight: %lf\n",temp->src,temp->dst,temp->weight);
  }

}

void printEdge(struct edge * temp){

  printf("Src: %d\tDest: %d\tWeight: %lf\n",temp->src,temp->dst,temp->weight);
  return;

}

struct gheap * InitFileGHeap(char * filename){

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
  struct gheap * heap1 = initHeap(numEdges,sizeof(struct edge),&edgeMin);

  int v1 = 0;
  int v2 = 0;
  double w = 0.0;
  struct edge * temp = (struct edge *) malloc(sizeof(struct edge));
  while(fscanf(file,"%d %d %lf\n",&v1,&v2,&w) != EOF){
    printf("%d %d %f\n",v1,v2,w);
    temp->src = v1;
    temp->dst = v2;
    temp->weight = w;
    insertHeap(heap1, temp);
  }
  free(temp);
  fclose(file);
  return heap1;
}












