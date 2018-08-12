if __name__ == "__main__":
    S = input()
    ok = True
    if S[0] != 'A':
        ok = False
    cnt = 0
    for x in S[2:-1]:
        if x == "C":
            cnt += 1
    if cnt != 1:
        ok = False
    cnt = 0
    for x in S:
        if x.isupper():
            cnt += 1
    if cnt != 2:
        ok = False
    if ok:
        print ("AC")
    else:
        print ("WA")