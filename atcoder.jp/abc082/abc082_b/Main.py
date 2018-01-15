if __name__ == "__main__":
    S = list(input())
    T = list(input())
    S.sort()
    T.sort()
    T = list(reversed(T))
    if S < T:
        print ("Yes")
    else:
        print ("No")
