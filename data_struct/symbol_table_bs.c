#include "symbol_table_bs.h"

struct symbol_table_bs * ST(){

  struct symbol_table_bs * temp =(struct symbol_table_bs *) malloc(sizeof(struct symbol_table_bs));
  temp->size=0;

  // set the initial capcacity as 1024
  temp->capacity = 1024;

  temp->key = (char **) malloc(temp->capacity*sizeof(char *));
  temp->values = (int *) malloc(temp->capacity*sizeof(int));
  return temp;
}

void put(struct symbol_table_bs * st, char * key, int value){
  // Search for the key
  // Update if found
  // grow table if needed

}

int * get(struct symbol_table_bs * st,char * key){

  struct node * it_node = st->head;
  while (it_node != NULL){
    if(!strcmp(it_node->key,key)) return &it_node->value;
    it_node = it_node->next;
  }
  return NULL;
}

int size(struct symbol_table_bs * st){
  return st->size;
}

int contains(struct symbol_table_bs * st, char * key){
  return get(st,key) == NULL ? 0 : 1;
}

int isEmpty(struct symbol_table_bs * st){
  return st->size == 0 ? 1 : 0;
}



void delete_st(struct symbol_table_bs * st, char * key){
  // 3 cases:
  //  1. Key is the head of the linked list
  //  2. Key is the tail of the linked list
  //  3. Key is neither of the two
  struct node * it_node = st->head;
  while (it_node != NULL){
    if(!strcmp(it_node->key,key)){
      if(it_node == st->head){
        st->head = st->head->next;
      }
      else if(it_node == st->tail){
        st->tail = st->tail->prev;
      }
      else{
        struct node * prev_node = it_node->prev;
        struct node * next_node = it_node->next;
        prev_node->next = next_node;
        next_node->prev = prev_node;
      }
      free(it_node);
      st->size--;
      return;
    }
    it_node= it_node->next;
  }
  return;
}

char ** keys(struct symbol_table_bs * st){

  char ** key_it = (char **)malloc(st->size*sizeof(char *));
  struct node * it_node = st->head;
  int i;
  for(i=0;i<st->size;i++){
    key_it[i] = (char *)malloc(MAX_NUM_CHAR*sizeof(char));
    strcpy(key_it[i],it_node->key);
    it_node=it_node->next;
  }
  return key_it;
}

void cleanup_keys(struct symbol_table_bs * st, char ** keys){
  //printf("cleaning up\n");
  int i;
  for(i=0;i<st->size;i++){
    free(keys[i]);
  }
  free(keys);
  keys=NULL;

}
void printLL(struct symbol_table_bs * st){
  struct node * it_node = st->head;
  while(it_node != NULL){
    printf("Key: %s\tValue: %d\n",it_node->key,it_node->value);
    it_node = it_node->next;
  }
  printf("size: %llu\n",st->size);
}
/*
int main(void){
  struct symbol_table_bs * test = ST();
  put(test,"YOLO",3);
  put(test,"POOO",4);
  put(test,"FOO", 5);
  printLL(test);
  char ** key =keys(test);
  int i;
  for(i=0;i<test->size;i++){
    printf("Keys: %s\t",key[i]);
  }
  printf("\n");
  cleanup_keys(test, key);
  delete_st(test,"YOLO");
  printLL(test);
  return 0;
}

*/

