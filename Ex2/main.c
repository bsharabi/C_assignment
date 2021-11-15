#include <stdio.h>
#include "my_mat.h"
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define INFINITY 9999
#define V 10
int main() {
	int from, to;
	char ch;
	int graph[V][V] = { 0 };
	int distance[V][V];
	while (1) {
		int visited[V] = { 0 };
		ch = getchar();
		switch (ch)
		{
		case 'A':
			fiilGraph(&graph);
			Initialize(&distance, &graph);
			break;
		case 'B':
			scanf("%d %d", &from, &to);
			printf(Route(from, to, &graph, &visited) ? "True\n" : "False\n");
			break;
		case 'C':
			scanf("%d %d", &from, &to);
			FloydWarshall(&distance, V);
			printf((distance[from][to] >= INFINITY || distance[from][to] == 0) ? "-1\n" : "%d\n", distance[from][to]);
			break;
		case 'D':
			return 0;
		}
	}

}