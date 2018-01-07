if __name__ == "__main__":
    N, H = map(int, input().split())
    ab = []
    max_a = 0
    for i in range(N):
        a,b = map(int, input().split())
        max_a = max(max_a, a)
        ab.append([b, a])
    ab.sort()
    ab = list(reversed(ab))
    res = 0
    result = 2 ** 100
    
    for b,_ in ab:
        H -= b
        res += 1
        if H <= 0:
            result = min(result, res)
            break
        tmp = res + H // max_a
        if H % max_a != 0:
            tmp += 1
        result = min(result, tmp)
            
    print (result)
        
    