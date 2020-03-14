#ifndef SYMBOL_TABLE_RED_BLACK_BST
#define SYMBOLE_TABLE_RED_BLACK_BST

#include "stdio.h"
#include "string.h"
#include "stdlib.h"

enum color { RED, BLACK };

#define MAX_NUM_CHAR 1024

// Red-Black tree symbol table(2-3 tree, left-self leaning)

struct node {

  struct node * left_child;   // link to left child
  struct node * right_child;  // link to right child
  char * key;                 // Key
  int value;                  // associated value
  int n;                      // # of nodes in subtree rooted here
                              // root node gives you total number of nodes/keys
  enum color link;            // Color of link from parent to this node
};

struct symbol_table {
  struct node * root;
};

// Create a symbol table
struct symbol_table * ST();

// Create a new a node
struct node * createNode(char * key, int value, int n, enum color color_link);

// Check the link color
int isRed(struct node * x);

// Rotate a right red link to left link
struct node * rotateLeft(struct node * h);

// Rotate a left red link to right link
struct node * rotateRight(struct node * h);

// is the table empty?
int isEmpty(struct symbol_table * st);

// number of key-value pairs in the table
int size(struct symbol_table * st);

// number of key-value pairs rooted at node
int sizeNode(struct node * x);

// put key-value pair into the table
// ( remove key from table if value is null)
void put(struct symbol_table * st,char* key, int value);

// Value paired with key
// (NULL if key is absent)
int * get(struct symbol_table * st, char * key);

// is there a value paired with key?
int contains(struct symbol_table * st, char * key);

// Interchange from colors to maintain black balance
void filpColors(struct node * h);

// Idea is to return a iterator that will allow one to iterate through all keys
// but we will return a dynamically allocated array of all keys and
// programmer will have to free memory when done.
char ** keys_range(struct symbol_table * st,int lo, int hi);
char ** keys(struct symbol_table * st);
void cleanup_keys(struct symbol_table * st, char ** keys);

#endif
