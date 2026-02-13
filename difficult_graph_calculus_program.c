
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

#define MAX 100
#define INF 999999

typedef struct {
    int vertices;
    int adj[MAX][MAX];
} Graph;

void initGraph(Graph* g, int v) {
    g->vertices = v;
    for(int i = 0; i < v; i++) {
        for(int j = 0; j < v; j++) {
            g->adj[i][j] = (i == j) ? 0 : INF;
        }
    }
}

void addEdge(Graph* g, int src, int dest, int weight) {
    g->adj[src][dest] = weight;
    g->adj[dest][src] = weight;
}

int minDistance(int dist[], int visited[], int v) {
    int min = INF, min_index = -1;
    for(int i = 0; i < v; i++) {
        if(!visited[i] && dist[i] <= min) {
            min = dist[i];
            min_index = i;
        }
    }
    return min_index;
}

void dijkstra(Graph* g, int src) {
    int v = g->vertices;
    int dist[MAX], visited[MAX];

    for(int i = 0; i < v; i++) {
        dist[i] = INF;
        visited[i] = 0;
    }

    dist[src] = 0;

    for(int count = 0; count < v - 1; count++) {
        int u = minDistance(dist, visited, v);
        visited[u] = 1;

        for(int i = 0; i < v; i++) {
            if(!visited[i] && g->adj[u][i] != INF &&
               dist[u] != INF &&
               dist[u] + g->adj[u][i] < dist[i]) {
                dist[i] = dist[u] + g->adj[u][i];
            }
        }
    }

    printf("\nShortest distances from node %d:\n", src);
    for(int i = 0; i < v; i++) {
        printf("To %d -> %d\n", i, dist[i]);
    }
}

double f(double x) {
    return x*x*x - 2*x - 5;
}

double df(double x) {
    return 3*x*x - 2;
}

double newtonRaphson(double x0, int maxIter) {
    double x = x0;
    for(int i = 0; i < maxIter; i++) {
        double fx = f(x);
        double dfx = df(x);

        if(fabs(dfx) < 1e-6) {
            printf("Derivative too small. Stopping.\n");
            return x;
        }

        double x1 = x - fx/dfx;

        if(fabs(x1 - x) < 1e-6) {
            return x1;
        }

        x = x1;
    }
    return x;
}

int main() {
    int v, e;
    printf("Enter number of vertices: ");
    scanf("%d", &v);

    Graph g;
    initGraph(&g, v);

    printf("Enter number of edges: ");
    scanf("%d", &e);

    printf("Enter edges (src dest weight):\n");
    for(int i = 0; i < e; i++) {
        int s, d, w;
        scanf("%d %d %d", &s, &d, &w);
        addEdge(&g, s, d, w);
    }

    int source;
    printf("Enter source node for Dijkstra: ");
    scanf("%d", &source);

    dijkstra(&g, source);

    double guess;
    printf("\nNewton-Raphson Method to solve x^3 - 2x - 5 = 0\n");
    printf("Enter initial guess: ");
    scanf("%lf", &guess);

    double root = newtonRaphson(guess, 100);
    printf("Approximated Root: %.6lf\n", root);

    return 0;
}
