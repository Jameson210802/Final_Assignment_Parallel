# Description
This program implements a breadth first search on an adjacency matrix.
This is used to determine the shortest distance from the starting node to every other node in the graph.
This prints out those shortest distances.


# Input
This program takes in a text file that holds an adjacency matrix. an example is:
```text
5
0 1 1 0 0
1 0 0 1 0
0 0 0 1 0
0 0 0 0 1
0 0 0 0 0
```
This states that there are 5 nodes in the graph. The first line 
```text
0 1 1 0 0
```
states that node 0 (yes we start at 0) has no connections with 0, 3 and 4 but has connections with 1 and 2.
