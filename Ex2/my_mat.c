#include <stdio.h>
#include "my_mat.h"
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define INFINITY 111111111111111111
#define V 10
#define false 0
#define true 1
void Initialize()
{
	for (int i = 0;i < V;i++)
		for (int j = 0;j < V;j++)
			if (i == j)
				distance[i][j] = graph[i][j];
			else
				distance[i][j] = graph[i][j] ? graph[i][j] : INFINITY;
}
void fiilGraph() {
	for (int i = 0; i < V; i++)
		for (int j = 0; j < V; j++)
			scanf("%d", &graph[i][j]);
}
int Route(int from, int to) {
	if (from == to)
		return false;
	if (graph[from][to])
		return true;
	for (int i = 0;i < V;i++)
	{
		if (graph[from][i] && !visited[i]) {
			visited[i] = 1;
			if (Route(i, to))
				return true;
		}
	}
	return false;
}
void FloydWarshall(int vertices) {
	int from, to, via;
	for (from = 0;from < vertices;from++)
		for (to = 0;to < vertices;to++)
			for (via = 0;via < vertices;via++)
				distance[from][to] = MIN(distance[from][to], distance[from][via] + distance[via][to]);
}