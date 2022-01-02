#include "graph.h"
#include "minHeap.h"

char ch=0;
int v_size=0;
int e_size=0;
int *listVisited;
pnode head = NULL;
pnode tail = NULL;

void free_edge_cmd(pnode *head)
{
    if ((*head)->neighbours == NULL)
        return;
    pedge tempEdge = (*head)->neighbours;
    while (tempEdge)
    {
        pedge p_edge_free = tempEdge;
        tempEdge = tempEdge->next;
        e_size--;
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
    printf("|V| = %d ", v_size);
    printf("|E| = %d\n", e_size);

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
    if (v_size == 0)
        return;
    int i = 0;
    char *inputStream = calloc(i, sizeof(*inputStream));
    for (i = 0; (ch = getchar()) != '\n' && !isupper(ch); i++)
    {
        inputStream = realloc(inputStream, ((i + 1) * sizeof(*inputStream)));
        *(inputStream + i) = ch;
    }

    pnode *vert_created = calloc(v_size, sizeof(**vert_created));
    int number = v_size;
    int index_stream = 0;
    char ch = ' ';
    while (number && index_stream < i)
    {
        ch = *(inputStream + index_stream);
        if (ch == ' ' || ch == 'n')
        {
            index_stream++;
            continue;
        }
        int src = 0;
        while (isdigit(*(inputStream + index_stream)))
        {
            src *= 10;
            src += *(inputStream + index_stream) - '0';
            index_stream++;
        }
        ch = *(inputStream + index_stream);
        if (vert_created[src % v_size] == NULL)
        {
            pnode srcNode = malloc(sizeof(*srcNode));
            srcNode->id = src;
            srcNode->neighbours = NULL;
            srcNode->next = NULL;
            vert_created[src % v_size] = srcNode;
        }
        number--;
        if (number == 0 || ch == '\n' || ch == 'n' || *(inputStream + index_stream + 1) == 'n')
            continue;
        index_stream++;
        while (1)
        {
            int dest = 0;
            while (isdigit(*(inputStream + index_stream)))
            {
                dest *= 10;
                dest += *(inputStream + index_stream) - '0';
                index_stream++;
            }
            e_size++;
            index_stream++;
            pnode destnode;
            if (vert_created[dest % v_size] == NULL)
            {
                destnode = malloc(sizeof(*destnode));
                destnode->id = dest;
                destnode->neighbours = NULL;
                destnode->next = NULL;
                vert_created[dest % v_size] = destnode;
            }
            else
                destnode = vert_created[dest % v_size];
            pedge e = malloc(sizeof(*e));
            int weight = 0;
            while (isdigit(*(inputStream + index_stream)))
            {
                weight *= 10;
                weight += *(inputStream + index_stream) - '0';
                index_stream++;
            }
            e->weight = weight;
            e->dest = destnode;
            e->next = NULL;
            if (vert_created[src % v_size]->neighbours != NULL)
            {
                e->next = vert_created[src % v_size]->neighbours;
                vert_created[src % v_size]->neighbours = e;
            }
            else
            {
                vert_created[src % v_size]->neighbours = e;
            }
            if (ch == '\n' || ch == 'n' || *(inputStream + index_stream + 1) == 'n')
                break;
            index_stream++;
        }
    }
    for (int i = 0; i < v_size - 1; i++)
        vert_created[i]->next = vert_created[i + 1];
    (*head) = vert_created[0];
    if (*head)
        tail = vert_created[v_size - 1];
    free(vert_created);
    free(inputStream);
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
            e_size--;
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
            e_size--;
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
        v_size--;
        ch = getchar();
        return;
    }
    if (tempHead != NULL)
    {
        prevNode->next = tempHead->next;
        v_size--;
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
        v_size++;
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
    int i = 0;
    char *inputStream = calloc(i, sizeof(*inputStream));
    for (i = 0; (ch = getchar()) != '\n' && !isupper(ch); i++)
    {
        inputStream = realloc(inputStream, ((i + 1) * sizeof(*inputStream)));
        *(inputStream + i) = ch;
    }
    newNode->id = nodeId;
    newNode->neighbours = NULL;
    if (i < 3)
    {
        free(inputStream);
        return;
    }
    tempHead = *head;
    int index_stream = 0;
    char ch = ' ';
    while (index_stream < i)
    {
        ch = *(inputStream + index_stream);
        if (ch == ' ' || ch == '\n')
        {
            index_stream++;
            continue;
        }

        int dest = 0;
        while (isdigit(*(inputStream + index_stream)))
        {
            dest *= 10;
            dest += *(inputStream + index_stream) - '0';
            index_stream++;
        }
        index_stream++;
        e_size++;
        while (tempHead != NULL && tempHead->id != dest)
            tempHead = tempHead->next;
        if (tempHead == NULL)
            break;

        pedge e = malloc(sizeof(*e));
        int weight = 0;
        while (isdigit(*(inputStream + index_stream)))
        {
            weight *= 10;
            weight += *(inputStream + index_stream) - '0';
            index_stream++;
        }
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
        index_stream++;
    }
    free(inputStream);
}
int dijkstra(pnode *head, int src, int dest)
{
    listVisited = NULL;
    pnode tempHead = (*head);
    // Min Heap Memory O(|V|)
    Heap *heap = CreateHeap(v_size);
    if (heap == NULL)
    {
        printf("__Memory Issue__\n");
        return -1;
    }
    // O(V)
    while (tempHead)
    {
        tempHead->distance = (tempHead->id == src) ? 0 : MAX_INT;
        insert(heap, &tempHead);
        tempHead = tempHead->next;
    }

    while (heap->count)
    {
        pnode node = PopMin(heap);
        pedge edge = node->neighbours;
        while (edge)
        {
            int distance;
            distance = node->distance + edge->weight;

            if (distance < edge->dest->distance)
            {
                edge->dest->distance = distance;
                edge->dest->previous = node;
            }
            edge = edge->next;
        }
        heapify_top_bottom(heap, 0);
    }
    tempHead = (*head);
    while (tempHead)
    {
        if (tempHead->id == dest)
            break;
        tempHead = tempHead->next;
    }
    int path = tempHead->distance;
    if (path == MAX_INT)
    {
        listVisited = malloc(sizeof(int));
        listVisited[0] = path;
        free(heap->vert_arr);
        free(heap);
        return 1;
    }
    int size = 0;

    listVisited = malloc(size * sizeof(int));
    while (tempHead && tempHead->id != src)
    {
        size++;
        listVisited = realloc(listVisited, size * sizeof(int));
        listVisited[size - 1] = tempHead->id;
        tempHead = tempHead->previous;
    }
    size++;
    listVisited = realloc(listVisited, size * sizeof(int));
    listVisited[size - 1] = src;
    size++;
    listVisited = realloc(listVisited, size * sizeof(int));
    listVisited[size - 1] = path;
    tempHead = (*head);

    free(heap->vert_arr);
    free(heap);
    return size;
}
void shortsPath_cmd(pnode *head)
{
    int src, dest;
    scanf("%d %d", &src, &dest);
    int size = dijkstra(head, src, dest);
    if (size == -1)
        return;
    pnode tempHead = (*head);
    while (tempHead)
    {
        if (tempHead->id == dest)
        {
            printf("Dijsktra shortest path: %d\n", (tempHead->distance) < MAX_INT ? (tempHead->distance) : -1);
            break;
        }
        tempHead = tempHead->next;
    }
    free(listVisited);
    ch = getchar();
}
void swap(int *arr, int i, int j)
{
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}
void TSP_cmd(pnode *head)
{
    int count_cities;
    scanf("%d", &count_cities);
    int *cities = malloc(count_cities * sizeof(int));
    int i = 0;
    while ((count_cities - i))
        scanf("%d", &cities[i++]);
    ch = getchar();

    if (count_cities <= 1)
    {
        free(cities);
        cities = NULL;
        printf("TSP shortest path: 0\n");
        return;
    }
    int minDistance = MAX_INT;
    int *permute = malloc(count_cities * sizeof(int));
    for (int i = 0; i < count_cities; i++)
        permute[i] = i;
    int *temp_permute = calloc(count_cities, sizeof(int));
    int index_i = 0;
    int h = -1;
    while (index_i < count_cities)
    {
        if (temp_permute[index_i] < index_i)
        {
            if (h >= 0)
            {
                if (index_i % 2 == 0)
                    swap(permute, 0, index_i);
                else
                    swap(permute, temp_permute[index_i], index_i);
            }
            else
            {
                temp_permute[index_i] = 0;
                index_i--;
            }
            h++;
            int count = count_cities - 2;
            int distance = 0;
            int cityPath = dijkstra(head, cities[permute[0]], cities[permute[1]]);

            int *citiesPathList = malloc((cityPath - 1) * sizeof(int));
            int count_citiesPathList = cityPath - 1;
            if (listVisited[cityPath - 1] == MAX_INT)
            {
                free(listVisited);
                listVisited = NULL;
                free(citiesPathList);
                citiesPathList = NULL;
                temp_permute[index_i] += 1;
                index_i = 0;
                continue;
            }
            distance += listVisited[--cityPath];
            int p = 0;
            while (cityPath)
            {
                cityPath--;
                citiesPathList[p++] = listVisited[cityPath];
            }
            if (count == 0)
            {
                free(listVisited);
                listVisited = NULL;
                free(citiesPathList);
                citiesPathList = NULL;
                temp_permute[index_i] += 1;
                minDistance = MIN(distance, minDistance);
                index_i = 0;
                continue;
            }
            p = 2;
            int flag = 0;
            while (count)
            {
                for (int i = 0; i < count_citiesPathList; i++)
                {
                    if (cities[permute[p]] == citiesPathList[i])
                    {
                        p++;
                        flag = 1;
                        break;
                    }
                }
                if (flag)
                {
                    flag = 0;
                    count--;
                    continue;
                }
                free(listVisited);
                listVisited = NULL;
                cityPath = dijkstra(head, citiesPathList[count_citiesPathList - 1], cities[permute[p]]);

                if (listVisited[--cityPath] == MAX_INT)
                {
                    free(listVisited);
                    listVisited = NULL;
                    free(citiesPathList);
                    citiesPathList = NULL;
                    distance = MAX_INT;
                    flag = 1;
                    break;
                }
                distance += listVisited[cityPath];
                int index = count_citiesPathList;
                while (cityPath)
                {
                    for (int i = 0; i < count_citiesPathList; i++)
                    {
                        if (citiesPathList[i] == listVisited[cityPath - 1])
                        {
                            flag = 1;
                            break;
                        }
                    }
                    if (flag != 1)
                    {
                        citiesPathList = realloc(citiesPathList, (count_citiesPathList + 1) * sizeof(int));
                        citiesPathList[index++] = listVisited[cityPath - 1];
                        count_citiesPathList++;
                        flag = !flag;
                    }
                    flag = 0;
                    cityPath--;
                }
                p++;
                count--;
                if (count)
                {
                    free(listVisited);
                    listVisited = NULL;
                }
            }
            minDistance = MIN(distance, minDistance);
            if (flag != 1)
            {
                free(citiesPathList);
                citiesPathList = NULL;
                free(listVisited);
                listVisited = NULL;
            }
            temp_permute[index_i] += 1;
            index_i = 0;
            if (citiesPathList != NULL)
                free(citiesPathList);
            if (listVisited != NULL)
                free(listVisited);
        }
        else
        {
            temp_permute[index_i] = 0;
            index_i++;
        }
    }

    free(cities);
    cities = NULL;
    free(permute);
    permute = NULL;

    free(temp_permute);
    temp_permute = NULL;
    // printf("\n___________________________________\n");
    if (minDistance < MAX_INT)
        printf("TSP shortest path: %d\n", minDistance);
    else
        printf("TSP shortest path: -1\n");
    // printf("\n___________________________________\n");

    if (ch == ' ')
        ch = getchar();
}
