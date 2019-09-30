#ifndef SYMBOL_TABLE_BS
#define SYMBOL_TABLE_BS

#include "stdio.h"
#include "string.h"
#include "stdlib.h"

#define MAX_NUM_CHAR 1024

// Sequential Symbol Table using arrays
// No duplicates
// New value replaces old value of same key
// No key assosiated with NULL

struct symbol_table_bs {
  char ** keys;
  int * values;
  unsigned long long size;
  unsigned long long capacity;

};

// Create a symbol table
struct symbol_table_bs * ST();

// put key-value pair into the table
// ( remove key from table if value is null)
void put(struct symbol_table_bs * st,char* key, int value);

// Value paired with key
// (NULL if key is absent)
int * get(struct symbol_table_bs * st, char * key);

// remove key(and its value) from table
void delete_st(struct symbol_table_bs *st, char * key);

// is there a value paired with key?
int contains(struct symbol_table_bs * st, char * key);

// is the table empty?
int isEmpty(struct symbol_table_bs * st);

// smallest key
char * min_bs(struct symbol_table_bs * st);

// largest key
char * max_bs(struct symbol_table_bs * st);

// largest key less than or equal to the key
char * floor_bs(struct symbol_table_bs * st, char * key);

// smallest key greater than or equal to key
char * ceiling(struct symbol_table_bs * st, char * key);

// number of keys less than key
int rank(struct symbol_table_bs * st, char * key);

// key of rank k
char * select_bs(struct symbol_table_bs * st, int k);

// delete smallest key
void deleteMin(struct symbol_table_bs * st);

// delete largest key
void deleteMax(struct symbol_table_bs * st);

// number of key-value pairs in the table
int size(struct symbol_table_bs * st);

// num of keys in [lo..hi]
int size_range(struct symbol_table_bs * st, int lo, int hi);


// Idea is to return a iterator that will allow one to iterate through all keys
// but we will return a dynamically allocated array of all keys and
// programmer will have to free memory when done.
char ** keys_rangs(struct symbol_table_bs * st,int lo, int hi);
char ** keys(struct symbol_table_bs * st);
void cleanup_keys(struct symbol_table_bs * st, char ** keys);

// Print Link List
void printBS(struct symbol_table_bs * st);

#endif
