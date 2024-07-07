#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct Link {
    int hop, dest, wt;
};

struct Network {
    int H, L;
    struct Link* link;
};

void main() {
    int H, L, S, i, j;
    
    printf("Distance Vector Routing using Bellman Ford Algorithm\n");
    printf("Enter number of hops: ");
    scanf("%d", &H);
    printf("Enter number of links: ");
    scanf("%d", &L);

    struct Network* n = (struct Network*)malloc(sizeof(struct Network));
    n->H = H;
    n->L = L;
    n->link = (struct Link*)malloc(n->L * sizeof(struct Link));

    for (i = 0; i < L; i++) {
        printf("Link %d: enter source, destination, and weight: ", i + 1);
        scanf("%d %d %d", &n->link[i].hop, &n->link[i].dest, &n->link[i].wt);
    }

    printf("Enter source node: ");
    scanf("%d", &S);

    int dist[H];
    for (i = 0; i < H; i++)
        dist[i] = INT_MAX;
    dist[S] = 0;

    for (i = 1; i < H; i++) {
        for (j = 0; j < L; j++) {
            int u = n->link[j].hop;
            int v = n->link[j].dest;
            int wt = n->link[j].wt;
            if (dist[u] != INT_MAX && dist[u] + wt < dist[v])
                dist[v] = dist[u] + wt;
        }
    }

    for (i = 0; i < L; i++) {
        int u = n->link[i].hop;
        int v = n->link[i].dest;
        int wt = n->link[i].wt;
        if (dist[u] != INT_MAX && dist[u] + wt < dist[v]) {
            printf("Network contains negative weight cycle\n");
            return;
        }
    }

    printf("Hop\tDistance from source\n");
    for (i = 0; i < H; i++) {
        printf("%d\t%d\n", i, dist[i]);
    }

    free(n->link);
    free(n);
}

