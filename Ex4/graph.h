#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX_INT 99999999
char ch;
int v_size;
int e_size;
int *listVisited;

typedef struct Node *pnode;
typedef struct Edge *pedge;
#ifndef __Edge_H__
#define __Edge_H__
typedef struct Edge
{
    int weight;
    pnode dest;
    struct Edge *next;
} edge, *pedge;
#endif
#ifndef __Node_H__
#define __Node_H__
typedef struct Node
{
    int id;
    int distance;
    pedge neighbours;
    struct Node *previous;
    struct Node *next;
} node, *pnode;
#endif

pnode head;
pnode tail;
void build_graph_cmd(pnode *head);
void insert_node_cmd(pnode *head);
void delete_node_cmd(pnode *head);
void unlink_neighbors_cmd(pnode *head, int nodeId);
void printGraph_cmd(pnode *head);
void deleteGraph_cmd(pnode *head);
int dijkstra(pnode *head, int src, int dest);
void shortsPath_cmd(pnode *head);
void TSP_cmd(pnode *head);
void free_edge_cmd(pnode *head);