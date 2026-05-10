all: connected_mp connected_mpi

connected_mp: connected_components_mp.cc 
		gcc -O2 -g -fopenmp connected_components_mp.cc -o connected_mp
connected_mpi:
		mpicc connected_components_mpi.cc -o connected_mpi
clean:
		rm connected_mp connected_mpi