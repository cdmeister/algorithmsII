#include "symbol_table_bs.h"

struct symbol_table_bs * ST(){

  struct symbol_table_bs * temp =(struct symbol_table_bs *) malloc(sizeof(struct symbol_table_bs));
  temp->size=0;

  // set the initial capcacity as 1024
  temp->capacity = 1024;

  temp->keys = (char **) malloc(temp->capacity*sizeof(char *));
  int i;
  for(int i = 0;i<temp->capacity;i++){
    temp->keys[i] = NULL;
  }
  temp->values = (int *) malloc(temp->capacity*sizeof(int));
  return temp;
}

// number of keys less than key
int rank(struct symbol_table_bs * st, char * key){

  int lo = 0, hi = st->size-1;
  while(lo<=hi){
    int mid = lo + (hi - lo)/2;
    int cmp = strcmp(key,st->keys[mid]);
    if( cmp > 0) lo = mid +1;
    else if(cmp < 0) hi = mid - 1;
    else return mid;

  }
  return lo;
}

// put key-value pair into the table
void put(struct symbol_table_bs * st,char* key, int value){

  // rank() searches for the key if found
  // if not found then rank will tell us where to put it
  int i = rank(st,key);
  if( i<st->size && strcmp(st->keys[i],key) == 0){
    st->values[i] = value;
    return;
  }
  st->keys[st->size]=(char *) malloc(MAX_NUM_CHAR * sizeof(char));
  int j;
  for(j = st->size;j>i;j--){
    strcpy(st->keys[j],st->keys[j-1]);
    st->values[j] = st->values[j-1];
  }
  strcpy(st->keys[i],key);
  st->values[i] = value;
  ++st->size;
}

// Value paired with key
// (NULL if key is absent)
//int * get(struct symbol_table_bs * st, char * key);

void printBS(struct symbol_table_bs * st){
  int i;
  for(i=0;i<st->size;i++){
    printf("Key: %s\tValue: %d\n",st->keys[i],st->values[i]);
  }
}


int main(void){
  struct symbol_table_bs * test = ST();
  put(test,"YOLO",3);
  put(test,"POOO",4);
  put(test,"FOO", 5);
  put(test,"APPLE", 5);
  put(test,"WWWAZ",3);
  printBS(test);
  return 0;
}


