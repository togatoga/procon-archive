if __name__ == "__main__":
    Q,H,S,D = map(int, input().split())
    N = int(input())
    result = 2 ** 100

    TQ = N * 4 * Q
    result = min(result, TQ)

    TH = N * 2 * H
    result = min(result, TH)

    TS = N * S
    result = min(result, TS)

    if (N >= 2):
        tmp_N = N
        res = tmp_N // 2 * D
        tmp_N -=  tmp_N // 2 * 2

        TQ = tmp_N * 4 * Q
        result = min(result, TQ + res)
        TH = tmp_N * 2* H
        result = min(result, TH + res)
        TS = tmp_N * S
        result = min(result, TS + res)

    print (result)
