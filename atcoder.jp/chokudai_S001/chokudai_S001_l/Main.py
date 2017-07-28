from collections import defaultdict

if __name__ == '__main__':
    N = int(input())
    A = list(map(int, input().split()))
    A = list(map(lambda x : x - 1, A))
    B = [0] * (N + 1)
    for x in range(N):
        B[A[x]] = x
    cnt = 0
    for x in range(N):
        if (x == B[x]):
            continue
        v1 = A[x]
        p1 = B[v1]

        p2 = B[x]
        v2 = A[p2]
        A[p1],A[p2] = A[p2],A[p1]
        B[v1] = p2
        B[v2] = p1
        cnt += 1
    if (cnt > N):
        print ("NO")
    else:
        if ((N - cnt) % 2):
            print ('NO')
        else:
            print ('YES')
