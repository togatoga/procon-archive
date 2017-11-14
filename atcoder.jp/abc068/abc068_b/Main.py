if __name__ == "__main__":
    N = int(input())
    if N <= 1:
        print (1)
        exit()

    res_cnt = 0
    res = 0
    for x in range(N + 1):
        cnt = 0
        y = x
        while (y > 1):
            if y % 2 == 0:
                y //= 2
                cnt += 1
            else:
                break
        if cnt > res_cnt:
            res_cnt = cnt
            res = x
    print (res)
