#include "symbol_table_bs.h"

struct symbol_table * ST(){

  struct symbol_table * temp =(struct symbol_table *) malloc(sizeof(struct symbol_table));
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
int rank(struct symbol_table * st, char * key){

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
void put(struct symbol_table * st,char* key, int value){

  // rank() searches for the key if found
  // if not found then rank will tell us where to put it
  int i = rank(st,key);
  if( i<st->size && strcmp(st->keys[i],key) == 0){
    st->values[i] = value;
    return;
  }
  // reallocate if needed
  if(st->size == st-> capacity){
    printf("Resizing before: %llu  after:%llu\n",st->capacity, st->capacity*2);
    st->capacity*=2;
    char ** temp_keys = realloc(st->keys,st->capacity*sizeof(char *));
    int * temp_values = realloc(st->values,st->capacity*sizeof(int));
    if(temp_keys) st->keys = temp_keys;
    if(temp_values)  st->values = temp_values;
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

int size(struct symbol_table * st){
  return st->size;
}

int isEmpty(struct symbol_table * st){
  return st->size == 0 ? 1 : 0;
}

char * min_bs(struct symbol_table * st){
  return st->keys[0];
}

char * max_bs(struct symbol_table * st){
  return st->keys[st->size-1];
}

char * select_bs(struct symbol_table * st, int k){
  return st->keys[k];
}

int contains(struct symbol_table * st, char * key){
  return get(st,key) == NULL ? 0 : 1;
}

// Value paired with key
// (NULL if key is absent)
int * get(struct symbol_table * st, char * key){

  if(isEmpty(st)) return NULL;
  int i = rank(st, key);
  if(i < st->size && strcmp(st->keys[i],key) == 0) return st->values+i;
  else return NULL;

}

void printST(struct symbol_table * st){
  int i;
  for(i=0;i<st->size;i++){
    printf("Key: %s\tValue: %d\n",st->keys[i],st->values[i]);
  }
}

char ** keys(struct symbol_table * st){

  char ** key_it = (char **) malloc(st->size*sizeof(char *));
  int i;
  for(i=0;i<st->size;i++){
    key_it[i] =(char *) malloc(MAX_NUM_CHAR*sizeof(char));
    strcpy(key_it[i],st->keys[i]);
  }
  return key_it;
}


void cleanup_keys(struct symbol_table * st, char ** keys){

  //printf("cleaning up\n");
  int i;
  for(i=0;i<st->size;i++){
    free(keys[i]);
  }
  free(keys);
  keys=NULL;
}
/*
int main(void){
  struct symbol_table * test = ST();
  put(test,"YOLO",3);
  put(test,"POOO",4);
  put(test,"FOO", 5);
  put(test,"APPLE", 5);
  put(test,"WWWAZ",3);
  put(test,"POOO",99);
  put(test,"FAO", 1234);
  printST(test);
  return 0;
}

*/
