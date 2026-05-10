import matplotlib.pyplot as plt
import csv



def get_data(file_name, x: list, y: list,node):
    with open(file_name, mode="r") as file:
        csv_file = csv.DictReader(file)
        for lines in csv_file:
            if node == lines["nodes"]:
                x.append(int(lines["tasks"]))
                y.append(float(lines["time"]))




def main():

    files = ["mpi_connected.csv",]

    node_list = ["1","2"]

    for file in files:
        for node in node_list:

            x = []
            y = []

            get_data(file, x, y,node)

            plt.plot(x, y,marker="o")

    

    plt.xlabel("tasks")
    plt.ylabel(" seconds (s)")
    plt.legend(["One Node Run","Two Node Run"])
    plt.savefig("par.png")
    plt.show()


if __name__ == "__main__":
    main()