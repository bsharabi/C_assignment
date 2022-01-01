#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
char ch = 0;
typedef struct _node_ *pnode;
typedef struct _edge_
{
    int weight;
    pnode dest;
    struct _edge_ *next;
} edge, *pedge;

typedef struct _node_
{
    int id;
    // int distance;
    // int visited;
    // struct _node_ *previous;
    pedge neighbours;
    struct _node_ *next;
} node, *pnode;
void build_graph_cmd(pnode *head);
void insert_node_cmd(pnode *head);
void delete_node_cmd(pnode *head);
void unlink_neighbors_cmd(pnode *head, int nodeId);
void printGraph_cmd(pnode *head);
void deleteGraph_cmd(pnode *head);
void dijkstra(pnode *head, int src);
void shortsPath_cmd(pnode *head);
void TSP_cmd(pnode *head);
void free_edge_cmd(pnode *head);
pnode head = NULL;
pnode tail = NULL;
int node_number = 0;

void free_edge_cmd(pnode *head)
{
    if ((*head)->neighbours == NULL)
        return;
    pedge tempEdge = (*head)->neighbours;
    while (tempEdge)
    {
        pedge p_edge_free = tempEdge;
        tempEdge = tempEdge->next;
        free(p_edge_free);
    }
    (*head)->neighbours = NULL;
}
void deleteGraph_cmd(pnode *head)
{
    pnode tempHead = *head;
    while (tempHead)
    {
        free_edge_cmd(&tempHead);
        pnode p_node_free = tempHead;
        tempHead = tempHead->next;
        free(p_node_free);
    }
    *head = NULL;
}
void printGraph_cmd(pnode *head)
{
    printf("-------------------Graph------------------------\n");
    pnode temp_head = *head;
    while (temp_head)
    {
        printf("src: %d ->", temp_head->id);
        pedge temp_edge = temp_head->neighbours;
        while (temp_edge)
        {
            printf("(%d, w=%d), ", temp_edge->dest->id, temp_edge->weight);
            temp_edge = temp_edge->next;
        }
        printf("\n");
        temp_head = temp_head->next;
    }
    printf("------------------------------------------------\n");
}
void build_graph_cmd(pnode *head)
{
    if (*head)
        deleteGraph_cmd(head);

    pnode *vert_created = calloc(node_number, sizeof(**vert_created));
    int number = node_number;
    (*head) = malloc(sizeof(**head));
    (*head)->neighbours = NULL;
    (*head)->next = NULL;
    (*head)->id = 0;
    *vert_created = *head;
    char carr[3] = {0};
    while (number)
    {
        if ((ch = getchar()) == 'n' || ch == ' ' || ch == '\n')
            continue;
        carr[0] = ch;
        int src = atoi(carr);
        ch = getchar();
        if (ch == '\n')
            break;
        number--;
        if ((ch = getchar()) == ' ' || ch == '\n' || isalpha(ch))
        {
            continue;
        }
        while (1)
        {
            carr[0] = ch;
            int dest = atoi(carr);
            pnode destnode;
            if (vert_created[dest] == NULL)
            {
                destnode = malloc(sizeof(*destnode));
                destnode->id = dest;
                destnode->neighbours = NULL;
                destnode->next = NULL;
                vert_created[dest] = destnode;
            }
            else
                destnode = vert_created[dest];
            pedge e = malloc(sizeof(*e));
            int weight;
            scanf("%d", &weight);
            e->weight = weight;
            e->dest = destnode;
            e->next = NULL;
            if (vert_created[src]->neighbours != NULL)
            {
                e->next = vert_created[src]->neighbours;
                vert_created[src]->neighbours = e;
            }
            else
            {
                vert_created[src]->neighbours = e;
            }
            if ((ch = getchar()) == '\n')
                break;
            if (ch == ' ')
                (ch = getchar());
            if (ch == 'n' || isalpha(ch) || ch == '\n')
                break;
        }
    }
    for (int i = 0; i < node_number - 1; i++)
    {
        if (vert_created[i + 1])
        {
            vert_created[i]->id = i;
            vert_created[i]->next = vert_created[i + 1];
        }
        else
        {
            pnode tmp = malloc(sizeof(pnode));
            tmp->neighbours = NULL;
            tmp->next = NULL;
            tmp->id = (i + 1);
            vert_created[i + 1] = tmp;
            vert_created[i]->next = tmp;
        }
    }
    if (*head)
        tail = vert_created[node_number - 1];
    free(vert_created);
}
void unlink_neighbors_cmd(pnode *head, int nodeId)
{

    pnode temp_head = *head;
    while (temp_head)
    {
        if (temp_head->neighbours == NULL)
        {
            temp_head = temp_head->next;
            continue;
        }
        pedge temp_edge = temp_head->neighbours->next;
        pedge temp_edge_previous = temp_head->neighbours;
        if (temp_edge_previous && temp_edge_previous->dest->id == nodeId)
        {
            temp_head->neighbours = temp_edge_previous->next;
            free(temp_edge_previous);
            temp_head = temp_head->next;
            continue;
        }
        while (temp_edge && temp_edge->dest->id != nodeId)
        {
            temp_edge = temp_edge->next;
            temp_edge_previous = temp_edge_previous->next;
        }
        if (temp_edge && temp_edge->dest->id == nodeId)
        {
            temp_edge_previous->next = temp_edge->next;
            free(temp_edge);
        }
        temp_head = temp_head->next;
    }
}
void delete_node_cmd(pnode *head)
{
    if (*head == NULL)
        return;
    int nodeId;
    scanf("%d", &nodeId);
    pnode tempHead = (*head)->next;
    pnode prevNode = *head;
    unlink_neighbors_cmd(head, nodeId);
    while (tempHead != NULL && tempHead->id != nodeId && prevNode->id != nodeId)
    {
        tempHead = tempHead->next;
        prevNode = prevNode->next;
    }

    if (prevNode->id == nodeId)
    {
        (*head) = prevNode->next;
        free_edge_cmd(&prevNode);
        free(prevNode);
        ch = getchar();
        return;
    }
    if (tempHead != NULL)
    {
        prevNode->next = tempHead->next;
        free_edge_cmd(&tempHead);
        free(tempHead);
    }
    ch = getchar();
}
void insert_node_cmd(pnode *head)
{
    pnode tempHead = *head;
    pnode newNode;
    int nodeId;
    scanf("%d", &nodeId);
    while (tempHead != NULL && tempHead->id != nodeId)
        tempHead = tempHead->next;
    if (tempHead == NULL)
    {
        newNode = malloc(sizeof(*newNode));
        tail->next = newNode;
        tail = newNode;
        newNode->next = NULL;
    }
    else
    {
        newNode = tempHead;
        free_edge_cmd(&newNode);
    }

    newNode->id = nodeId;
    newNode->neighbours = NULL;
    tempHead = *head;
    while ((ch = getchar()) != '\n' && !isalpha(ch))
    {
        if (ch == ' ')
            continue;
        int dest = ch - '0';
        while (tempHead != NULL && tempHead->id != dest)
            tempHead = tempHead->next;
        pedge e = malloc(sizeof(*e));
        int weight;
        scanf("%d", &weight);
        e->weight = weight;
        e->dest = tempHead;
        e->next = NULL;
        if (newNode->neighbours != NULL)
        {
            e->next = newNode->neighbours;
            newNode->neighbours = e;
        }
        else
            newNode->neighbours = e;
        tempHead = *head;
    }
}
// void shortsPath_cmd(pnode *head)
// {
//     int src, dest;
//     scanf("%d %d", &src, &dest);
//     dijkstra(head, src);
// }
int main()
{
    while (ch != '\n')
    {
        switch (ch)
        {
        case 'A':
            scanf("%d", &node_number);
            build_graph_cmd(&head);
            printGraph_cmd(&head);
            break;
        case 'B':
            insert_node_cmd(&head);
            printGraph_cmd(&head);
            break;
        case 'D':
            delete_node_cmd(&head);
            printGraph_cmd(&head);
            break;
        case 'T':
            printf("%c", ch);
            ch = getchar();
            // TSP_cmd(&head)
            break;
        case 'S':
            printf("%c", ch);

            ch = getchar();
            // shortsPath_cmd(&head)
            break;
        }
        if (isalpha(ch))
            continue;
        if (ch == '\n')
            break;
        ch = getchar();
    }
    deleteGraph_cmd(&head);
    return 0;
}