#include "symbol_table.h"

struct symbol_table * ST(){

  struct symbol_table * temp = malloc(sizeof(struct symbol_table));
  temp->size=0;
  memset(temp->list,0,MAX_SIZE*sizeof(struct node *));
  return temp;
}

void put( int key, char * value){




}

int main(void){
  return 0;
}



