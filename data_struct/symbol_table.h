#include "stdio.h"
#include "string.h"
#include "stdlib.h"

#define MAX_NUM_CHAR 15

// Sequential Symbol Table using linked list
// No duplicates
// New value replaces old value of same key
// No key assosiated with NULL

struct node {
  int key;
  void * value;
  struct node * next;
  struct node * prev;
};

struct symbol_table {
  unsigned long long size;
  struct node * head; // Head ptr
  struct node * tail; // Head ptr

};

// Create a symbol table
struct symbol_table * ST();

// put key-value pair into the table
// ( remove key from table if value is null)
void put(struct symbol_table * st,int key, char * value);

// Value paired with key
// (null if key is absent)
char * get(struct symbol_table * st, int key);

// remove key(and its value) from table
void delete(struct symbol_table *st, int key);

// is there a value paired with key?
int contains(int key);

// is the table empty?
int isEmpty(struct symbol_table * st);

// number of key-value pairs in the table
int size(struct symbol_table * st);

// Idea is to return a iterator that will allow one to iterate through all keys
// but we will return a dynamically allocated array of all keys and
// programmer will have to free memory when done.
void * keys(struct symbol_table * st);

// Print Link List
void printLL(struct symbol_table * st);

struct node * createNode();
