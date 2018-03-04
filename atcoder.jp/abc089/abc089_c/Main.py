from collections import defaultdict
if __name__ == "__main__":
    dic = defaultdict(int)
    N = int(input())
    for i in range(N):
        S = input()
        if S[0] in "M A R C H":
            dic[S[0]] += 1
    res = []
    if len(dic) < 3:
        print(0)
        exit(0)
    value = 1
    for key in dic:
        val = dic[key]
        res.append(val)
        value *= val
    if len(dic) == 3:
        print(value)
        exit(0)
    result = 0
    if len(dic) == 4:
        for i in res:
            result += value // i
    if len(dic) == 5:
        for i in range(len(res)):
            for j in range(i + 1, len(res)):
                result += value // (res[i] * res[j])
    print(result)
