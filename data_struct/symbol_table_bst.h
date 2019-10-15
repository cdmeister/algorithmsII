#ifndef SYMBOL_TABLE_BST
#define SYMBOLE_TABLE_BST

#include "stdio.h"
#include "string.h"
#include "stdlib.h"

#define MAX_NUM_CHAR 1024

struct node {

  struct node * left_child;   // link to left child
  struct node * right_child;  // link to right child
  struct node * parent;       // parent of node
  char * key;                 // Key
  int value;                  // associated value
  int n;                      // # of nodes in subtree rooted here
                              // root node gives you total number of nodes/keys
};

struct symbol_table {
  struct node * root;
};

// Create a symbol table
struct symbol_table * ST();

// put key-value pair into the table
// ( remove key from table if value is null)
void put(struct symbol_table * st,char* key, int value);

// Value paired with key
// (NULL if key is absent)
int * get(struct symbol_table * st, char * key);

// is there a value paired with key?
int contains(struct symbol_table * st, char * key);

// is the table empty?
int isEmpty(struct symbol_table * st);

// smallest key
char * min_bs(struct symbol_table * st);

// largest key
char * max_bs(struct symbol_table * st);

// largest key less than or equal to the key
char * floor_bs(struct symbol_table * st, char * key);

// smallest key greater than or equal to key
char * ceiling(struct symbol_table * st, char * key);

// delete smallest key
void deleteMin(struct symbol_table * st);

// delete largest key
void deleteMax(struct symbol_table * st);

// remove key(and its value) from table
void delete_st(struct symbol_table *st, char * key);


// number of key-value pairs in the table
int size(struct symbol_table * st);
int sizeNode(struct node * x);

// Idea is to return a iterator that will allow one to iterate through all keys
// but we will return a dynamically allocated array of all keys and
// programmer will have to free memory when done.
char ** keys(struct symbol_table * st);
void cleanup_keys(struct symbol_table * st, char ** keys);

// Print Link List
void printST(struct symbol_table * st);

struct node * createNode();
void print_node(struct node * x);
void printLevel(struct node* root, int level,int save,
                        char ** key_it, unsigned long long * q);
void printLevelOrder(struct node* root, int save, char ** key_it);
int height(struct node* x);
int * getNode(struct node * x, char * key);
void putNode(struct node ** x, char * key, int value);
struct node *  minNode(struct node * x);
struct node *  maxNode(struct node * x);
struct node * floorNode(struct node * x, char * key);
struct node * deleteNode(struct node * x,char * key);
struct node * deleteMinNode(struct node * x);
struct node * deleteMaxNode(struct node * x);
struct node * createCopyNode(struct node * x);




#endif
