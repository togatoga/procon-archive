if __name__ == "__main__":
    S = input()
    N = len(S)
    for i in range(N):
        left = i
        right = N - 1
        ok = True
        while (left <= right):
            if (S[left] == S[right]):
                left += 1
                right -= 1
            else:
                ok = False
                break
        if (ok):
            print (i)
            exit()
    print (N - 1)
