if __name__ == "__main__":
    N, A, B, C, D = map(int, input().split())
    # if A > B:
    #     A, B = B, A
    rest = N - 2

    for k in range(rest + 1):
        #minus
        l = rest + 1 - k
        left = A + C * k - l * D
        right = A + D * k - l * C
        # print(k, left, right)
        if left <= B and B <= right:
            print("YES")
            exit(0)
    print("NO")
