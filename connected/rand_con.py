import random
import sys



n = int(sys.argv[1])
m = int(sys.argv[2])

with open("big_graph.txt","w") as f:

    f.write(f"{n} {m}\n")


for _ in range(0,m):    

    x = random.randint(0,n -1 )
    y = random.randint(0,n - 1)

    # if(x==y):
    #     continue

    with open("big_graph.txt","a") as f:

        f.write(f"{x} {y}\n")


     


