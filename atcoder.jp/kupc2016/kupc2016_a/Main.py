if __name__ == "__main__":
    N,A,B = map(int, input().split())
    T = []
    for x in range(N):
        x = int(input())
        T.append(x)
    res = 0
    for x in T:
        if (A <= x and x < B):
            continue
        res += 1
    print (res)
