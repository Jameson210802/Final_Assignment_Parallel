#!/usr/bin/env bash



thread_num=(1 2 4 8 10)



for num in "${thread_num[@]}"; do
    echo "testing with $num threads:"
    export OMP_NUM_THREADS=$num
    ./connected_mp big_graph.txt
done

echo "PARALLEL TEST DONE!!"