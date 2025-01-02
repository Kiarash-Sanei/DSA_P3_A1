#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int* nieghbor;
    int size;
    int shortest;
    int times;
} node;

void dfs(node* nodes, int index, int trail, int n) 
{
    int shortest = nodes[index].shortest + 1;
    for (int i = 0; i < nodes[index].size; i++)
    {
        node* current = nodes + nodes[index].nieghbor[i];
        if (shortest < current->shortest)
        {
            current->shortest = shortest;
            current->times = 1;
            dfs(nodes, current - nodes, trail + 1, n);
        }
        else if (shortest = current->shortest && trail <= n )
        {
            current->times += 1;
            dfs(nodes, current - nodes, trail + 1, n);
        }
    }
}

int main() 
{
    int n, m;
    scanf("%d %d", &n, &m);
    node nodes[n];
    for (int i = 0; i < n; i++)
    {
        nodes[i].nieghbor = (int*)malloc(m * sizeof(int));
        nodes[i].size = 0;
        nodes[i].shortest = __INT32_MAX__;
        nodes[i].times = 0;
    }
    nodes[0].shortest = 0;

    for (int i = 0; i < m; i++)
    {
        int a,b;
        scanf("%d %d", &a, &b);
        a--;
        b--;
        nodes[a].nieghbor[nodes[a].size] = b;
        nodes[a].size++;
        nodes[b].nieghbor[nodes[b].size] = a;
        nodes[b].size++;
    }

    dfs(nodes, 0, 1, n);

    printf("%d\n", nodes[n - 1].times);
    
    return 0;
}