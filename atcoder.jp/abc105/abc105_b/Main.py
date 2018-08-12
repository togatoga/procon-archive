if __name__ == "__main__":
    N = int(input())
    for x in range(0, 100):
        y = N - 4 * x
        if y < 0:
            break
        if y % 7 == 0:
            print ("Yes")
            exit(0)
    print ("No")