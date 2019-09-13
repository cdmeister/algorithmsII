#include "stdio.h"
#include "string.h"
#include "stdlib.h"

#define MAX_SIZE 10
#define MAX_NUM_CHAR 15

// No duplicates
// New value replaces old value of same key
// No key assosiated with NULL

struct node {
  int key;
  void * value;
  struct node * next;
};

struct symbol_table {
  unsigned long long size;
  struct node * list[MAX_SIZE];

};

// Create a symbol table
struct symbol_table * ST();

// put key-value pair into the table
// ( remove key from table if value is null)
void put(int key, char * value);

// Value paired with key
// (null if key is absent)
char * get(int key);

// remove key(and its value) from table
void delete(int key);

// is there a value paired with key?
int contains(int key);

// is the table empty?
int isEmpty(struct symbol_table * st);

// number of key-value pairs in the table
int size(struct symbol_table * st);

// All the keys in the table
char * keys(struct symbol_table * st);

struct node * createNode();