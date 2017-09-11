if __name__ == "__main__":
    S = input()
    A = 2 ** 100
    Z = 2 ** 100
    res = 0
    for x,y in enumerate(S):

        if y == 'A':
            A = min(A,x)
        if y == 'Z':
            Z = x
            res = max(res, (Z - A) + 1)
    print (res)
