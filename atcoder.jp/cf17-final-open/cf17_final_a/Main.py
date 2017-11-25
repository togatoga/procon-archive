if __name__ == "__main__":
    S = input()
    text = "AKIHABARA"
    if S[0] == 'K':
        S = 'A' + S[:]
    while (True):
        update = False
        for i in range(len(S) - 1):
            if S[i] == 'H' and S[i + 1] == 'B':
                S = S[:i+1] + 'A' + S[i+1:]
                update = True
                break
            if S[i] == 'B' and S[i + 1] == 'R':
                S = S[:i + 1] + 'A' + S[i+1:]
                update = True
                break
        if not update:
            break
    if S[-1] == 'R':
        S = S[:] + 'A'
    if S == text:
        print ("YES")
    else:
        print ("NO")
