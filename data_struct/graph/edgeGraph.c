#include "edgeGraph.h"

struct node * createNode(int src, int dest, double weight){
  //printf("Creating New Node with key %s\tvalue %d\n",key,value);
  struct node * temp = (struct node * )malloc(sizeof(struct node));
  temp->src = src;
  temp->dest = dest;
  temp->weight = weight;
  temp->next = NULL;
  return temp;
}

/* Create a V-vertex graph */
struct Graph * InitEmptyGraph(int numVertices, int numEdges){

  struct Graph * temp = (struct Graph *) malloc(sizeof(struct Graph));
  temp->numVertices = numVertices;
  temp->numEdges = numEdges;
  temp->adjlist = (struct node **)malloc(numVertices*sizeof(struct node *));
  temp->visited = (int *)malloc(numVertices*sizeof(int *));

  int i;
  for(i=0;i<temp->numVertices;i++){
    temp->adjlist[i]=NULL;
    temp->visited[i]=0;
  }

  return temp;
}


struct Graph * InitFileGraph(char * filename){

  FILE * file = fopen(filename,"r");
  if(file == NULL)
  {
    printf("Error!");
    exit(1);
  }

  int numVertices = 0;
  int numEdges = 0;
  double weight = 0.0;

  fscanf(file,"%d\n",&numVertices);
  fscanf(file,"%d\n",&numEdges);
  printf("NumVerticeis: %d NumEdges: %d\n",numVertices,numEdges);
  struct Graph * temp = InitEmptyGraph(numVertices,numEdges);

  int v1 = 0;
  int v2 = 0;
  double w = 0.0;
  while(fscanf(file,"%d %d %lf\n",&v1,&v2,&w) != EOF){
    printf("%d %d %f\n",v1,v2,w);
    addEdge(temp,v1,v2,w);
    addEdge(temp,v2,v1,w);
  }
  fclose(file);
  return temp;
}

void addEdge(struct Graph * graph, int src, int dest, double weight){
  struct node * temp = createNode(src, dest, weight);
  temp->next = graph->adjlist[src];
  graph->adjlist[src] = temp;

}

void printGraph(struct Graph * graph){

  int i=0;
  for(;i<graph->numVertices;i++){
    printf("Vertex %d: ",i);
    struct node * head = graph->adjlist[i];
    while(head){
      printf("%d\t",head->dest);
      head=head->next;
    }
    printf("\n");
  }

}

int V(struct Graph * graph){
  return graph->numVertices;
}

int E(struct Graph * graph){
  return graph->numEdges;
}


struct node * adj(struct Graph * graph, int v){
  return graph->adjlist[v];
}


char * toString(struct Graph * graph){
  return NULL;
}


int main(int argc, char ** argv){

  struct Graph * graph =InitFileGraph(argv[1]);
  printGraph(graph);
  return 0;


}

