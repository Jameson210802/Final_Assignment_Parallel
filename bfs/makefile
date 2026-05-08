all: bfs_mp bfs_mpi

bfs_mpi: bfs_mpi.c
		mpicc bfs_mpi.c -o bfs_mpi

bfs_mp: bfs_mp.c 
		gcc -O2 -g -fopenmp bfs_mp.c -o bfs_mp

clean:
		rm bfs_mp bfs_mpi