import fractions
if __name__ == "__main__":
    A, B, C, D = map(int, input().split())
    A -= C
    B -= D
    W = abs(A)
    H = abs(B)
    if W == 0 or H == 0:
        print(0)
        exit()
    res = W + H - 1
    g = fractions.gcd(W, H)
    print(res - g + 1)
