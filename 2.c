#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct
{
    int *neighbor;
    int size;
    int shortest;
    int path;
} Node;

void bfs(Node *nodes, int n)
{
    int *queue = (int *)malloc(n * sizeof(int));
    int front = 0, rear = 0;

    queue[rear++] = 0;
    nodes[0].shortest = 0;
    nodes[0].path = 1;

    while (front < rear)
    {
        int current = queue[front++];
        for (int i = 0; i < nodes[current].size; i++)
        {
            int neighbor = nodes[current].neighbor[i];
            if (nodes[neighbor].shortest == INT_MAX)
            {
                nodes[neighbor].shortest = nodes[current].shortest + 1;
                nodes[neighbor].path = nodes[current].path;
                queue[rear++] = neighbor;
            }
            else if (nodes[neighbor].shortest == nodes[current].shortest + 1)
            {
                nodes[neighbor].path += nodes[current].path;
            }
        }
    }

    free(queue);
}

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);

    Node nodes[n];
    for (int i = 0; i < n; i++)
    {
        nodes[i].neighbor = (int *)malloc(n * sizeof(int));
        nodes[i].size = 0;
        nodes[i].shortest = INT_MAX;
        nodes[i].path = 0;
    }

    for (int i = 0; i < m; i++)
    {
        int a, b;
        scanf("%d %d", &a, &b);
        a--;
        b--;
        nodes[a].neighbor[nodes[a].size++] = b;
        nodes[b].neighbor[nodes[b].size++] = a;
    }

    bfs(nodes, n);

    printf("%d\n", nodes[n - 1].path);

    for (int i = 0; i < n; i++)
    {
        free(nodes[i].neighbor);
    }

    return 0;
}