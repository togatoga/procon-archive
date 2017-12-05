if __name__ == "__main__":
    N = int(input())
    res = 0
    for x in range(N):
        a,b = map(int, input().split())
        res += b - a + 1
    print (res)
