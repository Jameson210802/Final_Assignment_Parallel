#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <omp.h>


void bfs_adj_matrix(const int *adj, int n, int source, int *dist) {
    /* Initialize distances */

    #pragma omp parallel
    {

        for (int i = 0; i < n; i++) {
            dist[i] = INT_MAX;
        }
    
        int *queue = malloc(n * sizeof(int));
        int front = 0, back = 0;
    
        dist[source] = 0;
        queue[back++] = source;
    
        while (front < back) {
            int u = queue[front++];
    
            for (int v = 0; v < n; v++) {
                if (adj[u * n + v] && dist[v] == INT_MAX) {
                    dist[v] = dist[u] + 1;
    
                    #pragma omp critical
                    queue[back++] = v;
                }
            }
        }
    
        free(queue);
    }
}


void print_adjacency_matrix(const int *adj, int n) {
    printf("Adjacency matrix (%d x %d):\n", n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", adj[i * n + j]);
        }
        printf("\n");
    }
}



void read_adjacency_matrix(const char *filename, int *n, int **adj) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        fprintf(stderr, "Error opening file: %s\n", filename);
        exit(1);
    }

    /* Read number of vertices */
    if (fscanf(fp, "%d", n) != 1) {
        fprintf(stderr, "Failed to read graph size\n");
        exit(1);
    }

    /* Allocate adjacency matrix */
    *adj = (int *)malloc((*n) * (*n) * sizeof(int));
    if (!(*adj)) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    /* Read matrix entries */
    for (int i = 0; i < *n; i++) {
        for (int j = 0; j < *n; j++) {
            if (fscanf(fp, "%d", &((*adj)[i * (*n) + j])) != 1) {
                fprintf(stderr, "Error reading adjacency matrix\n");
                exit(1);
            }
        }
    }

    fclose(fp);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s graph.txt\n", argv[0]);
        return 1;
    }

    int n;
    int *adj;

    read_adjacency_matrix(argv[1], &n, &adj);
    print_adjacency_matrix(adj, n);

    int *dist = (int*)malloc(n * sizeof(int));

    bfs_adj_matrix(adj, n, 0, dist);

    printf("\nBFS distances from source 0:\n");
    for (int i = 0; i < n; i++) {
        printf("dist[%d] = %d\n", i, dist[i]);
    }

    free(adj);
    return 0;
}
