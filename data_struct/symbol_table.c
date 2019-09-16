#include "symbol_table.h"

struct symbol_table * ST(){

  struct symbol_table * temp = malloc(sizeof(struct symbol_table));
  temp->size=0;
  temp->head= NULL;
  temp->tail= NULL;
  return temp;
}

void put(struct symbol_table * st, int key, char * value){

  struct node * it_node = st->head;
  while(it_node != NULL){
    if(key == it_node->key){
      printf("match %d\n",key);
      it_node->value = (void *) value;
      return;
    }
    it_node=it_node->next;
  }
  struct node * new_node = (struct node *) malloc(sizeof(struct node));
  new_node->key = key;
  new_node->value = (void *) value;
  // If you have empty linked list only for the first node
  // Set the head ptr to the first node
  if(st->head == NULL){
    st->head = new_node;
    st->tail = new_node;
    new_node->next = NULL;
    new_node->prev = st->head;
  }
  else{
    struct node * prev_node = st->tail;
    prev_node->next = new_node;
    new_node->next = NULL;
    new_node->prev = prev_node;
    st->tail = new_node;
  }
  st->size++;
}

char * get(struct symbol_table * st,int key){

  struct node * it_node = st->head;
  while (it_node != NULL){
    if(it_node->key == key) return (char *) it_node->value;
    it_node = it_node->next;
  }
  return "ERROR";
}

int size(struct symbol_table * st){
  return st->size;
}

void delete(struct symbol_table * st, int key){
  // 3 cases:
  //  1. Key is the head of the linked list
  //  2. Key is the tail of the linked list
  //  3. Key is neither of the two
  struct node * it_node = st->head;
  while (it_node != NULL){
    if(it_node->key == key){
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

void * keys(struct symbol_table * st){

  int * key_it = malloc(st->size*sizeof(int));
  struct node * it_node = st->head;
  int i;
  for(i=0;i<st->size;i++){
    key_it[i]=it_node->key;
    it_node=it_node->next;
  }
  return (void *) key_it;
}

void printLL(struct symbol_table * st){
  struct node * it_node = st->head;
  while(it_node != NULL){
    printf("Key: %d\tValue: %s\n",it_node->key,(char *)it_node->value);
    it_node = it_node->next;
  }
  printf("size: %llu\n",st->size);
}

int main(void){
  struct symbol_table * test = ST();
  put(test,3,"YOLO");
  put(test,4,"POOO");
  put(test,5,"FOO");
  printLL(test);
  int * key =(int *) keys(test);
  int i;
  for(i=0;i<test->size;i++){
    printf("Keys: %d\t",key[i]);
  }
  free(key);
  printf("\n");
  delete(test,4);
  printLL(test);
  return 0;
}



