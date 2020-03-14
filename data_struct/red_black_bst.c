#include "red_black_bst.h"

//https://stackoverflow.com/questions/10066709/passing-struct-pointer-to-function-in-c


void print_node(struct node * x){
  if(x == NULL){ printf("NULL Node\n"); return;}
  printf("Key: %s\tValue:%d\tLink:%s\t",x->key,x->value,isRed(x)?"RED":"BLACK");
  printf("Size:%d\n",sizeNode(x));
}

struct symbol_table * ST(){
  struct symbol_table * temp = (struct symbol_table *) malloc(sizeof(struct symbol_table));
  temp->root = NULL;
  return temp;
}


struct node * createNode(char * key, int value, int n, enum color color_link){

    struct node * temp = (struct node *) malloc(sizeof(struct node));
    temp->key = (char *) malloc(MAX_NUM_CHAR * sizeof(char));
    strcpy(temp->key,key);
    temp->value = value;
    temp->n = n;
    temp->left_child = NULL;
    temp->right_child = NULL;
    temp->link = color_link;
    return temp;
}


int isRed(struct node * x){
  if (x == NULL) return 0;
  return (x->link == RED) ? 1 : 0;
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

void filpColors(struct node * h){
  //printf("Flipping Colors\n");
  h->link = RED;
  h->left_child->link  = BLACK;
  h->right_child->link = BLACK;

}



struct node * rotateLeft(struct node * h){

  struct node * x = h->right_child;
  h->right_child = x->left_child;
  x->left_child = h;

  x->link = h->link;
  h->link = RED;

  h->n = 1 + sizeNode(h->left_child) + sizeNode(h->right_child);
  return x;
}

struct node * rotateRight(struct node * h){

  struct node * x = h->left_child;
  h->left_child = x->right_child;
  x->right_child = h;

  x->link = h->link;
  h->link = RED;

  h->n = 1 + sizeNode(h->left_child) + sizeNode(h->right_child);
  return x;

}


int * getNode(struct node * h, char * key){

  if( h == NULL) return NULL;
  int cmp = strcmp(h->key,key);
  if(cmp > 0)return getNode(h->left_child,key);
  else if(cmp < 0)return getNode(h->right_child,key);
  else return &h->value;
}

int * get (struct symbol_table * st, char * key){
  return getNode(st->root,key);
}


int contains(struct symbol_table * st, char * key){
  return get(st,key) == NULL ? 0 : 1;
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
      //printf("Key: %s\tValue: %d \n", root->key, root->value);
      if(save){
        unsigned long long index = *q;
        key_it[index] = malloc(MAX_NUM_CHAR*sizeof(char));
        strcpy(key_it[index],root->key);
        index++;
        *q=index;
        //printf("index: %llu\n",index);
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
    int h = height(root);
    printf("Height of Tree: %d\n",h);
    int i;
    unsigned long long * q = malloc(sizeof(unsigned long long));
    *q=0;
    for (i=1; i<=h; i++) printLevel(root, i, save, key_it, q);
    free(q);
}

char ** keys(struct symbol_table * st){
  char ** key_it = (char **) malloc((long unsigned int)size(st)*sizeof(char *));
  printf("Size of st: %d\n",size(st));
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

struct node *  putNode(struct node * h, char * key, int value){

  //printf("Inserting Key: %s, Value: %d \n",key,value);
  if(h == NULL){
   // printf("Create new Node: %s,%d\n",key,value);
    h = createNode(key,value,1,RED);
    //printf("returning from creating new node \n");
    return h;
  }

  int cmp = strcmp(h->key,key);
  if (cmp > 0) {
    if( h->left_child != NULL){
     // printf("going left key: %s\n",h->left_child->key);
    }
    else{

      //printf("going left\n");
    }
    h->left_child=putNode(h->left_child,key,value);
  }
  else if(cmp < 0) {
    if( h->right_child != NULL){
     // printf("going right key: %s\n",h->right_child->key);
    }
    else{
      //printf("going right\n");
    }
    h->right_child=putNode(h->right_child,key,value);
  }
  else{
    //printf("Match found: %s\n",h->key);
    h->value = value;
  }
  //printf("Current Node\n");
  //print_node(h);

  //printf("Before Rotation\n");
  //print_node(h->left_child);
  //print_node(h->right_child);
  if(isRed(h->right_child) && !isRed(h->left_child)) h = rotateLeft(h);
  if(isRed(h->left_child) && isRed(h->left_child->left_child)) h = rotateRight(h);
  if(isRed(h->left_child) && isRed(h->right_child)) filpColors(h);

  h->n = sizeNode(h->left_child) + sizeNode(h->right_child) + 1;

  //printf("After Rotation\n");
  //print_node(h);
  //print_node(h->left_child);
  //print_node(h->right_child);

return h;

}

void put(struct symbol_table * st, char * key, int value){
  st->root = putNode(st->root,key,value);
  st->root->link=BLACK;
  //printf("root\n");
  //print_node(st->root);
  //print_node(st->root->left_child);
  //print_node(st->root->right_child);
  //printf("------------------------------------------\n");

}


//int main(void){
  //struct symbol_table * test = ST();
  //put(test,"C",3);
  //put(test,"B",4);
  //put(test,"A", 5);
  //put(test,"E", 5);
  //put(test,"R",3);
  //put(test,"C",99);
  //put(test,"H", 1234);
  //put(test,"M", 1234);
  //printST(test);
  //printf("%s\n",min_bs(test));
  //printf("%s\n",max_bs(test));
  //printf("%s\n",floor_bs(test,"G"));
  //printf("%s\n",floor_bs(test,"H"));
  //deleteMin(test);
  //delete_st(test,"E");
  //printST(test);
  //delete_st(test,"S");
  //printST(test);
  //printf("%s\n",floor_bs(test,"AAA"));
  //printf("%s\n",floor_bs(test,"FOO"));
  //printf("%s\n",floor_bs(test,"ZZZ"));
  //return 0;
//}


