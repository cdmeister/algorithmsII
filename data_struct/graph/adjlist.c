#include "adjlist.h"

static struct node * createNode(int vertex){
  //printf("Creating New Node with key %s\tvalue %d\n",key,value);
  struct node * temp = (struct node * )malloc(sizeof(struct node));
  temp->vertex = vertex;
  temp->next = NULL;
  temp->visited = 0;
  return temp;
}

/* Create a V-vertex graph with no edges */
struct Graph * InitEmptyGraph(int numVertices){

  struct Graph * temp = (struct Graph *) malloc(sizeof(struct Graph));
  temp->numVertices = numVertices;
  temp->numEdges = 0;
  temp->adjlist = (struct node **)malloc(numVertices*sizeof(struct node *));

  int i;
  for(i=0;i<temp->numVertices;i++){
    temp->adjlist[i]=NULL;
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

  fscanf(file,"%d\n",&numVertices);
  fscanf(file,"%d\n",&numEdges);

  struct Graph * temp = InitEmptyGraph(numVertices);
  temp->numEdges = numEdges;

  int v1 = 0;
  int v2 = 0;
  while(fscanf(file,"%d %d\n",&v1,&v2) != EOF){
    printf("%d %d\n",v1,v2);
    addEdge(temp,v1,v2);
    addEdge(temp,v2,v1);
  }
  fclose(file);
  return temp;
}

void addEdge(struct Graph * graph, int v, int w){
  struct node * temp = createNode(w);
  temp->next = graph->adjlist[v];
  graph->adjlist[v] = temp;

}

void printGraph(struct Graph * graph){

  int i=0;
  for(;i<graph->numVertices;i++){
    printf("Vertex %d: ",i);
    struct node * head = graph->adjlist[i];
    while(head){
      printf("%d\t",head->vertex);
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
