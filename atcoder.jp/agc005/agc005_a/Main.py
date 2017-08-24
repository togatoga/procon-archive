if __name__ == "__main__":
    X = input()
    S = 0
    T = 0
    res = len(X)
    for x in X:
        if (x == 'S'):
            S += 1
        else:
            if (S > 0):
                S -= 1
                res -= 2
    print (res)
