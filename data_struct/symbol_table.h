#ifndef SYMBOL_TABLE_LL
#define SYMBOL_TABLE_LL

#include "stdio.h"
#include "string.h"
#include "stdlib.h"

#define MAX_NUM_CHAR 1024

// Sequential Symbol Table using linked list
// No duplicates
// New value replaces old value of same key
// No key assosiated with NULL

struct node {
  char * key;
  int  value;
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
void put(struct symbol_table * st,char* key, int value);

// Value paired with key
// (NULL if key is absent)
int * get(struct symbol_table * st, char * key);

// remove key(and its value) from table
void delete_st(struct symbol_table *st, char * key);

// is there a value paired with key?
int contains(struct symbol_table * st, char * key);

// is the table empty?
int isEmpty(struct symbol_table * st);

// number of key-value pairs in the table
int size(struct symbol_table * st);

// Idea is to return a iterator that will allow one to iterate through all keys
// but we will return a dynamically allocated array of all keys and
// programmer will have to free memory when done.
char ** keys(struct symbol_table * st);
void cleanup_keys(struct symbol_table * st, char ** keys);

// Print Link List
void printST(struct symbol_table * st);

struct node * createNode();
#endif
