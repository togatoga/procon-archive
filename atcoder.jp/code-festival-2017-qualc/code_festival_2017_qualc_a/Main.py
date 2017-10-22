if __name__ == "__main__":
    S = input()
    for x in range(len(S) - 1):
        if S[x] == "A" and S[x + 1] == "C":
            print ("Yes")
            exit()
    print ("No")
