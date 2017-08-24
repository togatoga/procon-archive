MAX_N = 10 ** 5 + 10
if __name__ == "__main__":
    N,M = map(int, input().split())
    deg = [0] * MAX_N
    for x in range(M):
        a,b = map(int, input().split())
        deg[a] += 1
        deg[b] += 1
    for x in range(MAX_N):
        if (deg[x] % 2 != 0):
            print ("NO")
            exit()
    print ("YES")
