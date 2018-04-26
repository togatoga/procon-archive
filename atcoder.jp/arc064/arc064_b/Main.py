if __name__ == "__main__":
    S = input()
    N = len(S)
    if S[0] == S[-1]:
        if N % 2 == 0:
            print("First")
        else:
            print("Second")
    else:
        if N % 2 == 0:
            print("Second")
        else:
            print("First")
