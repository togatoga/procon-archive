if __name__ == "__main__":
    A,B = map(int, input().split())
    S = input().split('-')
    if (len(S) == 2):
        if (len(S[0]) == A and len(S[1]) == B):
            print ("Yes")
            exit(0)
    print ("No")