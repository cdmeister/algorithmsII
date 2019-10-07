#include "symbol_table_bst.h"

struct symbol_table * ST(){
  struct symbol_table * temp = (struct symbol_table *) malloc(sizeof(struct symbol_table));
  temp->root = NULL;
  return temp;
}


struct node * createNode(char * key, int value, int n){

    struct node * temp = (struct node *) malloc(sizeof(struct node));
    temp->key = (char *) malloc(MAX_NUM_CHAR * sizeof(char));
    strcpy(temp->key,key);
    temp->value = value;
    temp->n = n;
    temp->left_child = NULL;
    temp->right_child = NULL;
    temp->parent = NULL;
    return temp;
}


static int * getNode(struct node * x, char * key){

  if(x  == NULL){
    return NULL;
  }
  int cmp = strcmp(x->key,key);
  if (cmp > 0) getNode(x->left_child,key);
  else if(cmp < 0) getNode(x->right_child,key);
  else return &x->value;

}



int * get (struct symbol_table * st, char * key){
  return getNode(st->root,key);
}


int contains(struct symbol_table * st, char * key){
  return get(st,key) == NULL ? 0 : 1;
}

static void putNode(struct node ** x, char * key, int value){

  if((*x)  == NULL){
    //printf("1 I am here in putNode key= %s x=%p\n",key,(void *)(*x));
    *x = createNode(key,value,1);
    //printf("2 I am here in putNode key= %s x=%p key: %s\n",key,(void *)(*x),(*x)->key);

    return;
  }
  int cmp = strcmp((*x)->key,key);
  if (cmp > 0) {
    if( (*x)->left_child != NULL){
     // printf("going left key: %s\n",(*x)->left_child->key);
    }
    else{

      //printf("going left\n");
    }
    putNode(&(*x)->left_child,key,value);
  }
  else if(cmp < 0) {
    if( (*x)->right_child != NULL){
    //  printf("going right key: %s\n",(*x)->right_child->key);
    }
    else{
     // printf("going right\n");
    }
    putNode(&(*x)->right_child,key,value);
  }
  else{
   // printf("Match found: %s\n",(*x)->key);
    (*x)->value = value;
  }
  (*x)->n = sizeNode((*x)->left_child) + sizeNode((*x)->right_child) + 1;
}


void put(struct symbol_table * st, char * key, int value){
  //printf("Now inserting: %s\t%d \n", key,value);
  putNode(&st->root,key,value);
}

int size(struct symbol_table * st){
  return sizeNode(st->root);
}

int sizeNode(struct node * x){
  if(x == NULL) return 0;
  else return x->n;
}

static int height(struct node* node)
{
    if (node==NULL) return 0;
    else
    {
        /* compute the height of each subtree */
        int lheight = height(node->left_child);
        int rheight = height(node->right_child);

        /* use the larger one */
        if (lheight > rheight)
            return(lheight+1);
        else return(rheight+1);
    }
}

/* Print nodes at a given level */
static void printLevel(struct node* root, int level,int save,
                        char ** key_it, unsigned long long * q)
{
    //printf("Level: %d\n",level);
    if (root == NULL) return;
    if (level == 1) {
     // printf("Key: %s\tValue: %d \n", root->key, root->value);
      if(save){
        unsigned long long index = *q;
        key_it[index] = malloc(MAX_NUM_CHAR*sizeof(char));
        strcpy(key_it[index],root->key);
        index++;
        *q=index;
      }
    }
    else if (level > 1)
    {
        //printf("going left\n");
        printLevel(root->left_child, level-1,save,key_it,q);
        //printf("going right\n");
        printLevel(root->right_child, level-1,save,key_it,q);
    }
}


/* Function to print level order traversal a tree*/
static void printLevelOrder(struct node* root, int save, char ** key_it)
{
    int h = height(root);
    //printf("Height of Tree: %d\n",h);
    int i;
    unsigned long long * q = malloc(sizeof(unsigned long long));
    *q=0;
    for (i=1; i<=h; i++) printLevel(root, i, save, key_it, q);
    free(q);
}

char ** keys(struct symbol_table * st){
  char ** key_it = (char **) malloc(size(st)*sizeof(char *));
  printLevelOrder(st->root,1,key_it);
  return key_it;
}

void printST(struct symbol_table * st){
  printLevelOrder(st->root,0,NULL);
  return;
}

void cleanup_keys(struct symbol_table * st, char ** keys){

  //printf("cleaning up\n");
  int i;
  for(i=0;i<size(st);i++){
    free(keys[i]);
  }
  free(keys);
  keys=NULL;
}

/*int main(void){
  struct symbol_table * test = ST();
  put(test,"YOLO",3);
  put(test,"POOO",4);
  put(test,"FOO", 5);
  put(test,"APPLE", 5);
  put(test,"WWWAZ",3);
  put(test,"POOO",99);
  put(test,"FAO", 1234);
  printST(test);
  printf("--------Delete------\n");
  //delete_st(test,"FOO");
  printST(test);
  //printf("%s\n",floor_bs(test,"AAA"));
  //printf("%s\n",floor_bs(test,"FOO"));
  //printf("%s\n",floor_bs(test,"ZZZ"));
  return 0;
}
*/
