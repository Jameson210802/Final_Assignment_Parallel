#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <mpi.h>



void bfs_adj_matrix(const int *adj, int n, int source, int *dist,int rank) {
    /* Initialize distances */
    // for (int i = 0; i < n; i++) {
    //     dist[i] = INT_MAX;
    // }

    int *queue = malloc(n * sizeof(int));
    int front = 0, back = 0;

    dist[source] = 0;
    queue[back++] = source;

    while (front < back) {
        int u = queue[front++];

        for (int v = 0; v < n; v++) {
            if (adj[u * n + v] && dist[v] == INT_MAX) {
                dist[v] = dist[u] + 1 + rank;
                queue[back++] = v;
            }
        }
    }

    free(queue);
}


void intialize_dist(int *dist, int n)
{

    for (int i = 0; i < n; i++) 
    {
        dist[i] = INT_MAX;
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


void get_matrix_size(const char *filename, int *n, int **adj)
{

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

    int rank, size;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);


    int n;
    int *adj;

    // rank 0 loads the marix and the gets the matrix size.

    if(rank == 0) 
    {

        read_adjacency_matrix(argv[1], &n, &adj);
    }

    // sends n to all other ranks, 
    MPI_Bcast(&n,1,MPI_INT,0,MPI_COMM_WORLD);



    int rows_per_rank = n / size;

    int offset = rows_per_rank + rank; 





    int *local_adj = (int*)malloc(rows_per_rank * n * sizeof(int));



    int *local_dist = (int*)malloc(n * sizeof(int)); // holds the distacnes for the local 

    int *dist = NULL; 
    //get_matrix_size(argv[1]&n, &adj);

    if(rank == 0) 
    {
        dist = (int *)malloc(n*sizeof(int));
    }




    //intialize_dist(local_dist, rows_per_rank); 

    
  
    //MPI_Gather(local_dist, rows_per_rank, MPI_INT, dist, rows_per_rank, MPI_INT, 0, MPI_COMM_WORLD);


    MPI_Scatter(adj,rows_per_rank,MPI_INT,local_adj,rows_per_rank,MPI_INT,0,MPI_COMM_WORLD);




    












    // if(rank == 0)
    // {
    //     for(int i = 0; i < n; i++)
    //     {
    //         printf("dist[%d] = %d\n",i,dist[i]);
    //     }
    // }











    //bfs_adj_matrix(local_adj,rows_per_rank,0,local_dist,rank);



    


    //read_adjacency_matrix(argv[1], &n, &adj);
    //print_adjacency_matrix(adj, n);

    //int *dist = (int*)malloc(n * sizeof(int));

   // bfs_adj_matrix(adj, n, 0, dist);

//    if(rank == 0)
//     {
//        printf("\nBFS distances from source 0:\n");
//        for (int i = 0; i < n; i++)
//         {
//            printf("dist[%d] = %d\n", i, dist[i]);
//         }
//     }

    if(rank == 0) free(adj);
    //free(local_adj);
    if(rank == 0) free(dist);
    

    MPI_Finalize();
    return 0;
}
