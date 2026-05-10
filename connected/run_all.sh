#!/bin/bash


for nodes in 1 2; do

    for tasks in 8 16 32 64; do

    echo "Submitting Job with nodes: ${nodes} and tasks: ${tasks}"
    sbatch --nodes=$nodes --ntasks=$tasks run.sh
    done
done