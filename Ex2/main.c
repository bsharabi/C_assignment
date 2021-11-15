#include <stdio.h>
#include "my_mat.h"
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define INFINITY 9999
#define V 10
int distance[V][V] = { 0 };
int graph[V][V] = { 0 };
int visited[V] = { 0 };
int main() {
	int from, to;
	char ch;
	while (1) {
		ch = getchar();
		switch (ch)
		{
		case 'A':
			fiilGraph();
			Initialize();
			break;
		case 'B':
			scanf("%d %d", &from, &to);
			for(int i=0;i<V;i++)
			visited[i]=0;
			printf(Route(from, to) ? "True\n" : "False\n");
			break;
		case 'C':
			scanf("%d %d", &from, &to);
			FloydWarshall(V);
			printf((distance[from][to] >= INFINITY || distance[from][to] == 0) ? "-1\n" : "%d\n", distance[from][to]);
			break;
		case 'D':
			return 0;
		}
	}
}