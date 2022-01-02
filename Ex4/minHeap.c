#include "minHeap.h"

Heap *CreateHeap(int capacity)
{
    // one is number of heap
    Heap *h = (Heap *)malloc(sizeof(*h));
    // check if memory allocation is fails
    if (h == NULL)
    {
        printf("Memory Error!");
        return NULL;
    }
    h->count = 0;
    h->capacity = capacity;
    h->vert_arr = calloc(v_size, sizeof(**h->vert_arr));
    // check if allocation succeed
    if (h->vert_arr == NULL)
    {
        printf("Memory Error!");
        return NULL;
    }
    return h;
}
void insert(Heap *h, pnode *node)
{
    if (h->count < h->capacity)
    {
        h->vert_arr[h->count] = *node;
        heapify_bottom_top(h, h->count);
        h->count++;
    }
}
void heapify_bottom_top(Heap *h, int index)
{
    pnode temp;
    int parent_node = (index - 1) / 2;

    if (h->vert_arr[parent_node]->distance > h->vert_arr[index]->distance)
    {
        // swap and recursive call
        temp = h->vert_arr[parent_node];
        h->vert_arr[parent_node] = h->vert_arr[index];
        h->vert_arr[index] = temp;
        heapify_bottom_top(h, parent_node);
    }
}
void heapify_top_bottom(Heap *h, int parent_node)
{
    int left = parent_node * 2 + 1;
    int right = parent_node * 2 + 2;
    int min;
    pnode temp;

    if (left >= h->count || left < 0)
        left = -1;
    if (right >= h->count || right < 0)
        right = -1;

    if (left != -1 && h->vert_arr[left]->distance < h->vert_arr[parent_node]->distance)
        min = left;
    else
        min = parent_node;
    if (right != -1 && h->vert_arr[right]->distance < h->vert_arr[min]->distance)
        min = right;

    if (min != parent_node)
    {
        temp = h->vert_arr[min];
        h->vert_arr[min] = h->vert_arr[parent_node];
        h->vert_arr[parent_node] = temp;
        // recursive  call
        heapify_top_bottom(h, min);
    }
}
pnode PopMin(Heap *h)
{
    pnode pop;
    if (h->count == 0)
    {
        printf("\n__Heap is Empty__\n");
        return NULL;
    }
    // replace first node by last and delete last
    pop = h->vert_arr[0];
    h->vert_arr[0] = h->vert_arr[h->count - 1];
    h->count--;
    heapify_top_bottom(h, 0);
    return pop;
}
void print(Heap *h)
{
    int i;
    printf("____________Print Heap_____________\n");
    for (i = 0; i < h->count; i++)
    {
        printf("id -> %d distance -> %d\n", h->vert_arr[i]->id, h->vert_arr[i]->distance);
    }
}
