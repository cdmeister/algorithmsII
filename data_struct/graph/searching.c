#include "adjlist.h"
#include "deque.h"



void dfs_path(struct Graph * graph, int s, int d);
void bfs_path(struct Graph * graph, int s, int d);
void printPath(int * path,int s,int d,int curr);



int main(int argc, char ** argv){

  struct Graph * graph =InitFileGraph(argv[1]);
  printGraph(graph);

  dfs_path(graph,0,6);

  struct Graph * graph2 =InitFileGraph(argv[1]);
  printGraph(graph2);


  bfs_path(graph2,0,3);

  return 0;
}



/*dfs to find a path*/
void dfs_path(struct Graph * graph,int s,int d){

  /* mark the source visited*/
  graph->visited[s]=1;

  /* create deque to use as stack*/
  struct Deque * deque = createDeque();

  /* create a malloc node for deque */
  struct node * temp = createNode(s);

  /* push to front of deque */
  push_front(deque,temp);

  while(isEmpty(deque) != 1){
    struct node * candidate =(struct node  *)pop_front(deque);
    printf("%d\t",candidate->vertex);
    if(candidate->vertex == d){
      printf("Success!\n");
      free(temp);
      return;
    }
    else{
      struct node * child = graph->adjlist[candidate->vertex];
      while(child){
        if(graph->visited[child->vertex] ==0){
          graph->visited[child->vertex]=1;
          push_front(deque,child);
        }
        child=child->next;
      }
    }
  }
  printf("Failed!\n");
  free(temp);
  return;

}

//void bfs_path(struct Graph * graph,int s, int d);

/*bfs to find shortest path*/
void bfs_path(struct Graph * graph,int s,int d){

  /* mark the source visited*/
  graph->visited[s]=1;

  /* array to keep track of path for end*/
  int path[graph->numVertices];
  int i;
  for(;i<graph->numVertices;++i){
    path[i]=0;
  }

  /* create deque to use as stack*/
  struct Deque * deque = createDeque();

  /* create a malloc node for deque */
  struct node * temp = createNode(s);

  /* push to front of deque */
  push_back(deque,temp);

  while(isEmpty(deque) != 1){
    struct node * candidate =(struct node  *)pop_front(deque);
    printf("%d\t",candidate->vertex);
    if(candidate->vertex == d){
      printf("Success!\n");
      printPath(path,s,d,d);
      free(temp);
      return;
    }
    else{
      struct node * child = graph->adjlist[candidate->vertex];
      while(child){
        if(graph->visited[child->vertex] ==0){
          graph->visited[child->vertex]=1;
          push_back(deque,child);
          path[child->vertex]=candidate->vertex;
        }
        child=child->next;
      }
    }
  }
  printf("Failed!\n");
  free(temp);
  return;

}

void printPath(int * path, int s,int d, int curr){

  if(curr == s){
   printf("Shortest Path: %d->",curr);
   return;
  }
  printPath(path,s,d,path[curr]);
  if(curr==d){
    printf("%d\n",curr);
  }
  else{
    printf("%d->",curr);
  }
  return;
}
