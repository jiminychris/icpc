#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>

#ifndef INFINITY
#define INFINITY 1.0 / 0.0
#endif

struct node
{
    double x;
    double y;
    double penalty;
};

void node_new(struct node *nd, double x, double y, double penalty)
{
    nd->x = x;
    nd->y =  y;
    nd->penalty = penalty;
}

struct edge
{
    double weight;
    unsigned int target;
    struct edge *next;
};

void edge_new(struct edge *e, double weight, unsigned int target, struct edge* next)
{
    e->weight = weight;
    e->target = target;
    e->next = next;
}

double distance(struct node *a, struct node *b)
{
    return sqrt(pow(a->x-b->x, 2) + pow(a->y-b->y, 2));
}

int main(int argc, char *argv[])
{
    struct node nodes[1002];
    struct edge *edges = malloc(600000 * sizeof(*edges));
    struct edge *adj[1002];
    struct edge *next;
    unsigned int edgeCt;
    unsigned int n;
    unsigned int i, j;
    double x, y, penalty;
    char visited[1002];
    double weight[1002];
    double minValue;
    unsigned int minIndex;
    double result;
    
    node_new(&nodes[0], 0.0, 0.0, 0.0);
    scanf("%d", &n);
    while (n != 0)
    {
        edgeCt = 0;
        for (i=1; i<n+1; i++)
        {
            scanf("%lf %lf %lf", &x, &y, &penalty);
            node_new(&nodes[i], x, y, penalty);
        }
        node_new(&nodes[n+1], 100.0, 100.0, 0.0);

        for (i=0; i<n+1; i++)
        {
            penalty = 0.0;
            adj[i] = &edges[edgeCt];
            for (j=i+1; j<n+2; j++)
            {
                next = j == n+1 ? 0 : &edges[edgeCt + 1];
                edge_new(&edges[edgeCt++], 1.0+penalty+distance(&nodes[i], &nodes[j]), j, next);
                penalty += nodes[j].penalty; 
            }
        }

        for (i=0; i<1002; i++)
        {
            visited[i] = 0;
            weight[i] = INFINITY;
        }

        i = 0;
        weight[i] = 0.0;
        while (!visited[n+1])
        {
            visited[i] = 1;

            next = adj[i];
            while (next != 0)
            {
                if (weight[i] + next->weight < weight[next->target])
                    weight[next->target] = weight[i] + next->weight;
                next = next->next;
            }

            minValue = INFINITY;
            minIndex = -1;
            for (j=0; j<1002; j++)
            {
                if (!visited[j] && weight[j] < minValue)
                {
                    minValue = weight[j];
                    minIndex = j;
                }
            }

            i = minIndex;
        }

        result = floor((weight[n+1] * 1000) + .5) / 1000;

        printf("%.3lf\n", result);

        scanf("%d", &n);
    }

    return 0;
}