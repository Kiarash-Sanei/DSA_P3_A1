#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct
{
    int *neighbor;
    int size;
    int capacity;
    int shortest;
    long long path;
} Node;

void bfs(Node *nodes, int n)
{
    int *queue = (int *)malloc(n * sizeof(int));
    int front = 0, rear = 0;
    const long long MOD = 1000000007;

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
                nodes[neighbor].path = (nodes[neighbor].path + nodes[current].path) % MOD;
            }
        }
    }

    free(queue);
}

void addEdge(Node *nodes, int a, int b)
{
    if (nodes[a].size == nodes[a].capacity)
    {
        nodes[a].capacity = nodes[a].capacity == 0 ? 2 : nodes[a].capacity * 2;
        nodes[a].neighbor = (int *)realloc(nodes[a].neighbor, nodes[a].capacity * sizeof(int));
    }
    nodes[a].neighbor[nodes[a].size++] = b;
}

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);

    Node *nodes = (Node *)malloc(n * sizeof(Node));
    for (int i = 0; i < n; i++)
    {
        nodes[i].neighbor = NULL;
        nodes[i].size = 0;
        nodes[i].capacity = 0;
        nodes[i].shortest = INT_MAX;
        nodes[i].path = 0;
    }

    for (int i = 0; i < m; i++)
    {
        int a, b;
        scanf("%d %d", &a, &b);
        a--;
        b--;
        addEdge(nodes, a, b);
        addEdge(nodes, b, a);
    }

    bfs(nodes, n);

    printf("%lld\n", nodes[n - 1].path);

    for (int i = 0; i < n; i++)
    {
        free(nodes[i].neighbor);
    }
    free(nodes);

    return 0;
}
