import matplotlib.pyplot as plt
import csv



def get_data(file_name, x: list, y: list):
    with open(file_name, mode="r") as file:
        csv_file = csv.DictReader(file)
        for lines in csv_file:
          
            x.append(int(lines["threads"]))
            y.append(float(lines["time"]))




def main():

    files = ["mp_connected.csv",]



    for file in files:


        x = []
        y = []

        get_data(file, x, y)

        plt.plot(x, y,marker="o")

    

    plt.xlabel("threads")
    plt.ylabel(" seconds (s)")

    plt.savefig("mp_par.png")
    plt.show()


if __name__ == "__main__":
    main()