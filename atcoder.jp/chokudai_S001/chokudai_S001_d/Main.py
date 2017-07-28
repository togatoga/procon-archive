if __name__ == '__main__':
    N = int(input())
    res = list(map(int, input().split()))
    res = sorted(res)
    print (' '.join(map(str, res)))
