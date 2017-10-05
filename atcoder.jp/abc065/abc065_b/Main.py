if __name__ == "__main__":
    N = int(input())
    A = []
    for x in range(N):
        y = int(input())
        y -= 1
        A.append(y)
    pos = 0
    cnt = 0
    visited = set()
    while (cnt <= N + 1):
        visited.add(pos)
        if (pos == 1):
            print (cnt)
            exit()
        pos = A[pos]
        cnt += 1
        if pos in visited:
            break

    print (-1)
