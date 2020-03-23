#include "hash_table.h"

static unsigned int hash_function(char * key);
static struct node * create_node(char * key, int value);
static void printNode(struct node * new_node);
static void addNode(struct symbol_table * st, struct node * new_node, int index);

struct symbol_table * ST(){

  struct symbol_table * temp =(struct symbol_table *) malloc(sizeof(struct symbol_table));
  temp->llist = (struct linked_list *) malloc(HASH_TABLE_MAX_SIZE * sizeof(struct linked_list));
  int i;
  for(;i<HASH_TABLE_MAX_SIZE;i++){
    temp->llist[i].size=0;
    temp->llist[i].head= NULL;
    temp->llist[i].tail= NULL;
  }
   return temp;
}

static unsigned int hash_function(char * key){

  int hash = 0;
  int i;
  char * ptr = key;
  while(*ptr){
    hash += *ptr;
    printf("Character: %c Hash: %d\n", *ptr, hash);
    ++ptr;
  }
  hash = hash%HASH_TABLE_MAX_SIZE;
  printf("Key: %s Hash: %d\n", key, hash);
  return hash;

}


static struct node * create_node(char * key, int value){
  struct node * temp = (struct node * )malloc(sizeof(struct node));
  temp->key = (char *)malloc(MAX_NUM_CHAR*sizeof(char));
  strcpy(temp->key, key);
  temp->value = value;
  temp->prev = NULL;
  temp->next = NULL;
  return temp;
}

void put(struct symbol_table * st, char * key, int value){
  int index = hash_function(key);
  struct node *  new_node = create_node(key,value);
  addNode(st,new_node,index);
  //free(new_node);
}

int * get(struct symbol_table * st,char * key){
  int index = hash_function(key);
  struct linked_list * tempList = &st->llist[index];
  struct node * it_node = tempList->head;
  while(it_node != NULL){
    if(!strcmp(key,it_node->key)){
      return &it_node->value;
    }
    it_node=it_node->next;
  }
  return NULL;
}

int size(struct symbol_table * st){
  return st->size;
}

int contains(struct symbol_table * st, char * key){
  return get(st,key) == NULL ? 0 : 1;
}

int isEmpty(struct symbol_table * st){
  return st->size == 0 ? 1 : 0;
}



void delete_st(struct symbol_table * st, char * key){
}

char ** keys(struct symbol_table * st){
/*
  char ** key_it = (char **)malloc(st->size*sizeof(char *));
  struct node * it_node = st->head;
  int i;
  for(i=0;i<st->size;i++){
    key_it[i] = (char *)malloc(MAX_NUM_CHAR*sizeof(char));
    strcpy(key_it[i],it_node->key);
    it_node=it_node->next;
  }
  return key_it;
*/
return NULL;
}

void cleanup_keys(struct symbol_table * st, char ** keys){
/*
  printf("cleaning up\n");
  int i;
  for(i=0;i<st->size;i++){
    free(keys[i]);
  }
  free(keys);
  keys=NULL;
*/
}
void printST(struct symbol_table * st){
  int i;
  for(i = 0; i < HASH_TABLE_MAX_SIZE; i++){
    if(st->llist[i].size !=0){
      struct linked_list * tempList = &st->llist[i];
      struct node * it_node = tempList->head;
      printf("Index: %d\tSize: %llu\t", i,tempList->size);
      while(it_node != NULL){
        printf("Key: %s\tValue: %d\t\t",it_node->key,it_node->value);
        it_node = it_node->next;
      }
      printf("\n");
    }
  }
}


void printNode(struct node * victim){
  printf("Address: %p\tKey: %s\tValue: %d\n",victim,victim->key,victim->value);
}

void addNode(struct symbol_table * st, struct node * new_node, int index){
  struct linked_list * tempList = &st->llist[index];
  if(tempList->size == 0){

    tempList->head = new_node;
    tempList->tail = new_node;
    tempList->size++;

  }
  else {
    struct node * tail_node = tempList->tail;
    tail_node->next = new_node;
    printNode(tail_node);
    printNode(new_node);
    new_node->prev = tail_node;
    tempList->tail = new_node;
    tempList->size++;
  }
  return;
}

int main(void){
  struct symbol_table * test = ST();
  put(test,"YOLO",3);
  put(test,"YOOL",3);
  put(test,"LOOY",99);
  put(test,"POOO",4);
  put(test,"FOO", 5);
  printST(test);
  int * temp = get(test,"LOOY");
  printf("%d\n", *temp);
  /*char ** key =keys(test);
  int i;
  for(i=0;i<test->size;i++){
    printf("Keys: %s\t",key[i]);
  }
  printf("\n");
  cleanup_keys(test, key);
  delete_st(test,"YOLO");
  printST(test);
  */
  return 0;
}


