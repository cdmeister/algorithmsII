#include "union.h"


struct UF * createUnion(int num){

  struct UF * temp = (struct UF *) malloc(sizeof(struct UF));
  temp->id = (int *)malloc(sizeof(int)*num);
  temp->count = num;
  temp->size=num;
  int i;
  for(i=0;i<num;i++){
    temp->id[i]=i;
  }
  return temp;
}

static void printUnion(struct UF * uf){

  int i;
  for(i=0;i<uf->size;i++){
    printf("index %d: %d\n",i,uf->id[i]);
  }

  return;
}

int unionCount(struct UF * uf){

  return uf->count;

}
int unionConnected(struct UF * uf, int p, int q){

  return unionFind(uf,p) == unionFind(uf,q) ? 1 : 0;

}

int unionFind(struct UF * uf, int p){
  return uf->id[p];
}

void unionUnion(struct UF * uf, int p,int q){

  /* Put p and q into the same component */
  int pid = unionFind(uf,p);
  int qid = unionFind(uf,q);

  /* Nothing to do if p and q are already in the same component */
  if(pid == qid) return;


  int i;
  for(i=0;i<uf->size;i++){
    if(uf->id[i] == pid) uf->id[i] = qid;
  }
  --(uf->count);
}

struct UF * InitFileUnionFind(char * filename){

  FILE * file = fopen(filename, "r");
  if(file ==NULL){
    printf("ERROR!\n");
    exit(1);
  }

  int numVertices = 0;
  int v1, v2;
  fscanf(file,"%d\n",&numVertices);
  printf("NumVertices: %d\n",numVertices);

  struct UF * temp = createUnion(numVertices);
  while(fscanf(file,"%d %d\n",&v1,&v2) != EOF){

    printf("%d %d\n",v1,v2);
    unionUnion(temp,v1,v2);

  }
  fclose(file);
  return temp;

}

int main(int argc, char ** argv){
  struct UF * uf = InitFileUnionFind(argv[1]);
  printUnion(uf);
}
