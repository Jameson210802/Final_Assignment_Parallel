#!/bin/bash
#SBATCH --job-name=connected-mpi
#SBATCH --output=stdout.out
#SBATCH --error=stderr.err
#SBATCH --nodes=1
#SBATCH --ntasks=5
#SBATCH --time=00:05:00
#SBATCH --partition=gpu-a100-mig7
#SBATCH --account=class-cse4163
#SBATCH --no-requeue

# Load MPI module
module purge
module load spack-managed-x86-64_v3/v1.0
module load openmpi
srun -n $SLURM_NTASKS connected_mpi big_graph.txt