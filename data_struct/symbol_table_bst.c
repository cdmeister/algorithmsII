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


struct node * createCopyNode(struct node * x){

  struct node * temp = createNode(x->key,x->value,x->n);
  temp->left_child = x->left_child;
  temp->right_child = x->right_child;
  temp->parent=x->parent;
  return temp;

}

void print_node(struct node * x){
  if(x == NULL){ printf("NULL Node\n"); return;}
  printf("Key: %s\tValue:%d\n",x->key,x->value);
}


int * getNode(struct node * x, char * key){

  if(x  == NULL){
    return NULL;
  }
  int cmp = strcmp(x->key,key);
  if (cmp > 0) getNode(x->left_child,key);
  else if(cmp < 0) getNode(x->right_child,key);
  else return &x->value;

  return NULL;
}



int * get (struct symbol_table * st, char * key){
  return getNode(st->root,key);
}


int contains(struct symbol_table * st, char * key){
  return get(st,key) == NULL ? 0 : 1;
}

void putNode(struct node ** x, char * key, int value){

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

int isEmpty(struct symbol_table * st){
  return sizeNode(st->root) == 0 ? 1 : 0;
}

int height(struct node* x)
{
    //print_node(node);
    if (x==NULL) return 0;
    else
    {
        /* compute the height of each subtree */
        int lheight = height(x->left_child);
        int rheight = height(x->right_child);

        /* use the larger one */
        if (lheight > rheight)
            return(lheight+1);
        else return(rheight+1);
    }
}

/* Print nodes at a given level */
void printLevel(struct node* root, int level,int save,
                        char ** key_it, unsigned long long * q)
{
    //printf("Level: %d\n",level);
    if (root == NULL) return;
    if (level == 1) {
      printf("Key: %s\tValue: %d \n", root->key, root->value);
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
void printLevelOrder(struct node* root, int save, char ** key_it)
{
    int h = 4;//height(root);
    printf("Height of Tree: %d\n",h);
    int i;
    unsigned long long * q = malloc(sizeof(unsigned long long));
    *q=0;
    for (i=1; i<=h; i++) printLevel(root, i, save, key_it, q);
    free(q);
}

char ** keys(struct symbol_table * st){
  char ** key_it = (char **) malloc((long unsigned int)size(st)*sizeof(char *));
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

struct node *  minNode(struct node * x){
  //print_node(x);
  if(x->left_child == NULL) return x;
  struct node * temp = minNode(x->left_child);
  //printf("After\n");
  //print_node(x);
  //print_node(temp);
  return temp;
}


char * min_bs(struct symbol_table * st){
  return minNode(st->root)->key;
}

struct node *  maxNode(struct node * x){
  //print_node(x);
  if(x->right_child == NULL) return x;
  struct node * temp = maxNode(x->right_child);
  //printf("After\n");
  //print_node(x);
  //print_node(temp);
  return temp;
}


char * max_bs(struct symbol_table * st){
  return maxNode(st->root)->key;
}

struct node * floorNode(struct node * x, char * key){

  if(x == NULL) return NULL;
  //print_node(x);
  int cmp = strcmp(key,x->key);
  if(cmp == 0) return x;
  if(cmp < 0) {
   // printf("Going Left\n");
    //print_node(x);
    struct node * templ =floorNode(x->left_child,key);
   // printf("After Left\n");
  //  print_node(x);
   // print_node(templ);
    return templ;
  }
 // printf("Going Right\n");
 // print_node(x);
  struct node * temp = floorNode(x->right_child,key);
//  printf("After Right\n");
//  print_node(x);
//  print_node(temp);
  if(temp != NULL) return temp;
  else return x;
}

// floor of key is the largest key in the BST less than or equal to the key
// if you find the node then return that
// if the key is less than the node's key, then go left
// if the key is greater, then the floor of the key might be in the right
//  subtree only if there is a node with a key less than the key.
char * floor_bs(struct symbol_table * st, char * key){

 // printf("Start FLoor\n");
  struct node * temp = floorNode(st->root,key);
  if(temp == NULL) return NULL;
  else return temp->key;

}

struct node * deleteMinNode(struct node * x){

  // Keep going left until left_child is null.
  // then return right_child
    //print_node(x);
  if(x->left_child == NULL){
    //struct node * right_child = x->right_child;
    //printf("Before\n");
    //print_node(x);
    //print_node(right_child);
    //free(x->key);
    //free(x);
    //x=NULL;
    //printf("After\n");
    //print_node(x);
    //print_node(right_child);
    return x->right_child;
  }
  struct node * victim = deleteMinNode(x->left_child);
  x->left_child = victim;
  x->n = sizeNode(x->left_child) + sizeNode(x->right_child) + 1;
  return x;
}

void deleteMin(struct symbol_table * st){
  if(isEmpty(st)) return;
  deleteMinNode(st->root);
  return;

}

struct node * deleteMaxNode(struct node * x){

  // Keep going right until right_child is null.
  // then return left_child
  if(x->right_child == NULL){
    struct node * left_child = x->left_child;
    free(x);
    return left_child;
  }
  struct node * victim = deleteMaxNode(x->right_child);
  x->right_child = victim;
  x->n = sizeNode(x->left_child) + sizeNode(x->right_child) + 1;
  return x;
}

void deleteMax(struct symbol_table * st){
  if(isEmpty(st)) return;
  deleteMaxNode(st->root);
  return;

}

struct node * deleteNode(struct node * x,char * key){

  if( x == NULL) return NULL;
  int cmp = strcmp(key, x->key);
  if(cmp < 0)x->left_child=deleteNode(x->left_child,key);
  else if(cmp > 0) x->right_child = deleteNode(x->right_child,key);
  else{
    // Case 1: if the matching node only has one child
    if(x->left_child == NULL) return x->right_child;
    if(x->right_child == NULL) return x->left_child;

    // Case 2: if the matching node has two children
    //struct node * t = x;
    struct node * t = createCopyNode(x);
    struct node * mini = minNode(t->right_child);
    //print_node(mini);
    x=mini;
    //printf("Min key: ");
    //print_node(x);
    x->right_child = deleteMinNode(t->right_child);
    //printf("right child: ");
    //print_node(x->right_child);
    x->left_child = t->left_child;
    //printf("left child: ");
    //print_node(x->left_child);
    //printf("%p\n",(void *)t);
    //printf("%p\n",(void *)x);
    free(t);
  }
  x->n = sizeNode(x->left_child) + sizeNode(x->right_child) + 1;
  //  print_node(x);
  return x;
}

void delete_st(struct symbol_table * st,char * key){
  if(isEmpty(st)) return;
  st->root=deleteNode(st->root,key);
  return;

}



int main(void){
  struct symbol_table * test = ST();
  put(test,"S",3);
  put(test,"X",4);
  put(test,"E", 5);
  put(test,"A", 5);
  put(test,"R",3);
  put(test,"C",99);
  put(test,"H", 1234);
  put(test,"M", 1234);

  //printST(test);
  //printf("%s\n",min_bs(test));
  /*printf("%s\n",max_bs(test));
  printf("%s\n",floor_bs(test,"G"));
  printf("%s\n",floor_bs(test,"H"));*/
  //deleteMin(test);
  //delete_st(test,"E");
  //printST(test);
  delete_st(test,"S");
  //deleteMax(test);
  printST(test);
  //printf("%s\n",floor_bs(test,"AAA"));
  //printf("%s\n",floor_bs(test,"FOO"));
  //printf("%s\n",floor_bs(test,"ZZZ"));
  return 0;
}

