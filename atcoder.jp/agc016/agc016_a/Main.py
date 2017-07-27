def calc(x, S):
    res = set(S)
    cnt = 0
    while (len(res) != 1):
        cnt += 1
        t = ""
        N = len(S)
        for y in range(N - 1):
            if (S[y] == x):
                t += x
            elif (y + 1 < len(S) and S[y + 1] == x):
                t += x
            else:
                t += S[y]
        S = t
        res = set(S)
    return cnt


if __name__ == "__main__":
    S = input()
    res = set(S)
    result = 2 ** 50
    for x in res:
        result = min(result, calc(x, S))
    print (result)
