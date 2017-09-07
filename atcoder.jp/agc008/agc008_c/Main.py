def solve(A):
    # I + J + L
    res = 0
    I = A[0]
    J = A[3]
    L = A[4]

    O = A[1]
    if (I >= 1 and J >= 1 and L >= 1):
        tmp = 3 + ((I - 1) // 2 + (J - 1) // 2 + (L - 1) // 2) * 2 + O
        res = max(res, tmp)
    tmp = (I // 2 + J // 2 + L // 2) * 2 + O
    res = max(res, tmp)
    print (res)


if __name__ == "__main__":
    A = list(map(int, input().split()))
    solve(A)
