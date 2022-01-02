#include "graph.h"

#ifndef __Heap_H__
#define __Heap_H__

struct Heap
{
    int count;
    int capacity;
    pnode *vert_arr;
};
#endif
typedef struct Heap Heap;
Heap *CreateHeap(int capacity);
void insert(Heap *h, pnode *node);
void print(Heap *h);
void heapify_bottom_top(Heap *h, int index);
void heapify_top_bottom(Heap *h, int parent_node);
pnode PopMin(Heap *h);