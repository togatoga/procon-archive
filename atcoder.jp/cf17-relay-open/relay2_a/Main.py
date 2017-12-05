if __name__ == "__main__":
    K,A,B = map(int, input().split())
    left = 0
    right = 2 ** 100
    if A >= K:
        print (1)
        exit()
    if B >= A:
        print (-1)
        exit()
    while (right - left > 1):
        med = (right + left) // 2
        res = (A - B) * med
        if res >= K:
            right = med
        else:
            left = med
    # print ((A - B) * right)
    res = 2 * right
    for x in range(max(1, res - 100), res+10):
        a1 = x // 2
        a2 = x - a1
        tmp = A * a2 - B * a1
        if tmp >= K:
            print (x)
            exit()
