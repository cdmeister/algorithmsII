#ifndef UNION_H
#define UNION_H

#include "stdio.h"
#include "stdlib.h"

struct UF {
  int * id;
  int count;
  int size;
};

struct UF * createUnion(int num);

int unionCount(struct UF * uf);
int unionConnected(struct UF * uf, int p, int q);
int unionFind(struct UF * uf, int p);
void unionUnion(struct UF * uf, int p,int q);
#endif
