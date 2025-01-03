#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int *nieghbor;
    int size;
    int shortest;
    int path;
} node;

void bfs(node *nodes, int index, int trail, int n)
{
    int shortest = nodes[index].shortest + 1;
    trail++;
    if (trail == n)
    {
        return;
    }
    for (int i = 0; i < nodes[index].size; i++)
    {
        node *current = nodes + nodes[index].nieghbor[i];
        if (shortest < current->shortest)
        {
            current->shortest = shortest;
        }
    }
    for (int i = 0; i < nodes[index].size; i++)
    {
        node *current = nodes + nodes[index].nieghbor[i];
        bfs(nodes, current - nodes, trail, n);
    }
}

void pathCounter(node *nodes, int index, int trail, int n)
{
    trail++;
    if (trail == n)
    {
        return;
    }
    for (int i = 0; i < nodes[index].size; i++)
    {
        node *current = nodes + nodes[index].nieghbor[i];
        if (trail == current->shortest)
        {
            current->path++;
        }
    }
    for (int i = 0; i < nodes[index].size; i++)
    {
        node *current = nodes + nodes[index].nieghbor[i];
        pathCounter(nodes, current - nodes, trail, n);
    }
}

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);
    node nodes[n];
    for (int i = 0; i < n; i++)
    {
        nodes[i].nieghbor = (int *)malloc(m * sizeof(int));
        nodes[i].size = 0;
        nodes[i].shortest = __INT32_MAX__;
        nodes[i].path = 0;
    }
    nodes[0].shortest = 0;
    nodes[0].path = 1;

    for (int i = 0; i < m; i++)
    {
        int a, b;
        scanf("%d %d", &a, &b);
        a--;
        b--;
        nodes[a].nieghbor[nodes[a].size] = b;
        nodes[a].size++;
        nodes[b].nieghbor[nodes[b].size] = a;
        nodes[b].size++;
    }

    bfs(nodes, 0, 0, n);
    pathCounter(nodes, 0, 0, n);

    printf("%d\n", nodes[n - 1].path);

    return 0;
}