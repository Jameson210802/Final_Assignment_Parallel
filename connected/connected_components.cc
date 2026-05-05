#include <stdio.h>
#include <stdlib.h>

/* -------- Graph structure -------- */

typedef struct {
    int *neighbors;
    int degree;
} AdjList;

typedef struct {
    int N;
    AdjList *adj;
} Graph;

/* -------- Read graph from file -------- */
/* File format:
   N M
   u v
   u v
   ...
*/
void read_graph(const char *filename, Graph *g) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        fprintf(stderr, "Error opening file: %s\n", filename);
        exit(1);
    }

    int N, M;
    fscanf(fp, "%d %d", &N, &M);

    g->N = N;
    g->adj = (AdjList *)calloc(N, sizeof(AdjList));

    int *deg = (int *)calloc(N, sizeof(int));

    int u, v;
    for (int i = 0; i < M; i++) {
        fscanf(fp, "%d %d", &u, &v);
        deg[u]++;
        deg[v]++;
    }

    for (int i = 0; i < N; i++) {
        g->adj[i].neighbors = (int *)malloc(deg[i] * sizeof(int));
        g->adj[i].degree = 0;
    }

    rewind(fp);
    fscanf(fp, "%*d %*d");

    for (int i = 0; i < M; i++) {
        fscanf(fp, "%d %d", &u, &v);
        g->adj[u].neighbors[g->adj[u].degree++] = v;
        g->adj[v].neighbors[g->adj[v].degree++] = u;
    }

    free(deg);
    fclose(fp);
}

/* -------- Print connected components -------- */

void print_components(int *label, int N) {
    int *printed = (int *)calloc(N, sizeof(int));

    printf("\nConnected Components:\n");
    printf("---------------------\n");

    int comp_id = 0;
    for (int i = 0; i < N; i++) {
        if (!printed[i]) {
            printf("Component %d: ", comp_id++);
            int root = label[i];

            for (int v = 0; v < N; v++) {
                if (label[v] == root) {
                    printf("%d ", v);
                    printed[v] = 1;
                }
            }
            printf("\n");
        }
    }

    free(printed);
}

/* -------- Main -------- */

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s graph.txt\n", argv[0]);
        return 1;
    }

    Graph g;
    read_graph(argv[1], &g);

    int N = g.N;
    int *label = (int *)malloc(N * sizeof(int));

    for (int v = 0; v < N; v++) {
        label[v] = v;
    }

    int changed = 1;
    int iteration = 0;

    /* Label propagation */
    while (changed) {
        changed = 0;
        iteration++;

        for (int v = 0; v < N; v++) {
            int min_label = label[v];

            for (int i = 0; i < g.adj[v].degree; i++) {
                int u = g.adj[v].neighbors[i];
                if (label[u] < min_label) {
                    min_label = label[u];
                }
            }

            if (min_label < label[v]) {
                label[v] = min_label;
                changed = 1;
            }
        }
    }

    printf("Converged in %d iterations\n", iteration);
    printf("Vertex : Component\n");
    printf("-------------------\n");

    for (int v = 0; v < N; v++) {
        printf("%d : %d\n", v, label[v]);
    }

    print_components(label, N);

    /* Cleanup */
    for (int i = 0; i < N; i++) {
        free(g.adj[i].neighbors);
    }
    free(g.adj);
    free(label);

    return 0;
}
