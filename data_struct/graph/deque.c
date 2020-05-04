#include "deque.h"

static struct dequeNode * createDequeNode(void * data){

  struct dequeNode * temp = (struct dequeNode *)malloc(sizeof(struct dequeNode));
  temp->data=data;
  temp->next=NULL;
  temp->prev= NULL;
  return temp;

}

struct Deque * createDeque(){
  struct Deque * temp = (struct Deque *)malloc(sizeof(struct Deque));
  temp->head=NULL;
  temp->tail=NULL;
  return temp;
}

void push_front(struct Deque * deque, void * data){

  struct dequeNode * temp = createDequeNode(data);
  temp->next = deque->head;
  if(deque->tail == NULL){
    deque->tail = temp;
    deque->head = temp;
  }
  else{
    deque->head->prev = temp;
    deque->head = temp;
  }
  return;
}
void * pop_front(struct Deque * deque){

  if(deque->head ==NULL) return NULL;
  void * data = deque->head->data;
  struct dequeNode * temp = deque->head;

  if(deque->head == deque->tail){
    deque->head = NULL;
    deque->tail = NULL;
  }
  else{
    deque->head = deque->head->next;
    deque->head->prev=NULL;
  }

  free(temp);
  return data;
}

void printDeque(struct Deque * deque){

  struct dequeNode * head = deque->head;
  while(head){

    printf("%d\t",*(int*)head->data);
    head=head->next;

  }
  printf("\n");
  return;

}

void push_back(struct Deque * deque, void * data){

  struct dequeNode * temp = createDequeNode(data);
  temp->prev = deque->tail;
  if(deque->head == NULL){
    deque->tail = temp;
    deque->head = temp;
  }
  else{
    deque->tail->next = temp;
    deque->tail = temp;
  }

}

void *  pop_back(struct Deque * deque){

  if(deque->tail == NULL) return NULL;
  void * data = deque->tail->data;
  struct dequeNode * temp = deque->tail;
  if(deque->head == deque->tail){
    deque->head = NULL;
    deque->tail = NULL;
  }
  else{
    deque->tail = deque->tail->prev;
    deque->tail->next=NULL;
  }
  free(temp);
  return data;


}

int isEmpty(struct Deque * deque){

  if(deque->head == NULL && deque->tail == NULL){
    return 1;
  }
  else{
    return 0;
  }

}


/*
int main(int argc, char ** argv){

  int * a = (int *) malloc(sizeof(int));
  *a=1;

  int * b = (int *) malloc(sizeof(int));
  *b=2;

  int * c = (int *) malloc(sizeof(int));
  *c=3;

  struct Deque * deque =createDeque();

  push_front(deque, c);
  pop_back(deque);
  push_front(deque, b);
  push_front(deque, a);


  printDeque(deque);
  pop_back(deque);
  printDeque(deque);
  int * temp =(int *)pop_front(deque);
  printf("returned: %d\n",*temp);
  printDeque(deque);

  pop_front(deque);
  printDeque(deque);

  pop_front(deque);
  printDeque(deque);



  return 0;
}
*/
