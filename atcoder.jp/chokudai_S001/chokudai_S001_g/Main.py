MOD = 1000000007
if __name__ == '__main__':
    N = int(input())
    res = list(input().split())
    res = int("".join(res))
    print (res % MOD)
