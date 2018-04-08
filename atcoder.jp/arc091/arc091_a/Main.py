if __name__ == "__main__":
    N, M = map(int, input().split())
    if (N > M):
        N, M = M, N
    if (N == 1):
        print(max(1, M - 2))
        exit(0)
    result = (N - 2) * (M - 2)
    print(result)
