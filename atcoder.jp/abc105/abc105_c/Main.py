if __name__ == "__main__":
    N = int(input())
    for bit in range(0, 1 << 20):
        ans = "0" * 64
        ans = list(ans)
        res = 0

        base = 1
        idx = 0
        tmp_bit = bit
        while (tmp_bit > 0):
            if tmp_bit % 2 != 0:
                res += base
                ans[idx] = '1'
            tmp_bit = tmp_bit >> 1
            base *= 4
            idx += 2
        if N > res:
            continue
        
    
        for x in range(41, 0, -2):
            base = 2 ** x
            base *= -1
            if res + base >= N:
                res += base
                ans[x] = '1'
        if res == N:
            ans = "".join(reversed(ans))
            for i in range(len(ans)):
                if ans[i] == '1':
                    print (ans[i:])
                    exit(0)
            print (0)
            exit(0)

    
            
