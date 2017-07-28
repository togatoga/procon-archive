MOD = 1000000007
if __name__ == '__main__':
    N = int(input())
    res = list(map(int, input().split()))
    tmp = 0
    head = tail = 0
    cnt = 0
    while (True):
        if (tmp == N):
            cnt += 1
            tmp -= res[head]
            head += 1
        elif (tmp > N):
            tmp -= res[head]
            head += 1
            continue
        if (head >= N or tail >= N):
            break
        tmp += res[tail]
        tail += 1
    print (cnt)
