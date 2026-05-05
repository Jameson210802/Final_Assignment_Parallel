#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define DAMPING 0.85
#define EPSILON 1e-6
#define MAX_ITERS 100

int main(int argc, char *argv[]) {
    int verb = 0;
    if (argc < 2 || argc > 3) {
        printf("Usage: %s graph.txt -v(OPTIONAL)\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    if (argc == 3) {
	if (strcmp(argv[2],"-v") == 0) {
		verb = 1;
	}
    }

    int num_vertices, num_connections;
    fscanf(file, "%d %d", &num_vertices, &num_connections);

    // Allocate adjacency list
    int *out_degree = calloc(num_vertices, sizeof(int));
    int *src = malloc(num_connections * sizeof(int));
    int *dst = malloc(num_connections * sizeof(int));

    for (int i = 0; i < num_connections; i++) {
        fscanf(file, "%d %d", &src[i], &dst[i]);
        out_degree[src[i]]++;
    }
    fclose(file);

    // PageRank arrays
    double *pr = malloc(num_vertices * sizeof(double));
    double *new_pr = malloc(num_vertices * sizeof(double));

    // Initialize PageRank
    for (int i = 0; i < num_vertices; i++) {
        pr[i] = 1.0 / num_vertices;
    }

    // Main iteration loop
    for (int iter = 0; iter < MAX_ITERS; iter++) {
        // Base value
	if(verb) printf("New iteration: %d\n", iter);
        for (int i = 0; i < num_vertices; i++) {
            new_pr[i] = (1.0 - DAMPING) / num_vertices;
        }

        // Distribute rank contributions
        for (int i = 0; i < num_connections; i++) {
            int u = src[i];
            int v = dst[i];
	    if (verb) {
		printf("source node %d to goal node %d\n", u, v);
		printf("Rank before update: %f\n", new_pr[v]);
	    }
            new_pr[v] += DAMPING * pr[u] / out_degree[u];
	    if (verb) printf("Rank after update: %f\n", new_pr[v]);
        }

        // Convergence check (L1 norm)
        double diff = 0.0;
        for (int i = 0; i < num_vertices; i++) {
            diff += fabs(new_pr[i] - pr[i]);
            pr[i] = new_pr[i];
        }

	if (verb) {
		printf("\nUpdated PageRank values:\n");
		for (int i = 0; i < num_vertices; i++) {
			printf("Node %d: %.6f\n", i, pr[i]);
		}
	}



        if (diff < EPSILON) {
            printf("Converged after %d iterations\n", iter + 1);
            break;
        }
	if (verb) printf("================================\n\n");
    }

    // Output final PageRank values
    printf("\nFinal PageRank values:\n");
    for (int i = 0; i < num_vertices; i++) {
        printf("Node %d: %.6f\n", i, pr[i]);
    }

    // Cleanup
    free(out_degree);
    free(src);
    free(dst);
    free(pr);
    free(new_pr);

    return 0;
}
