if __name__ == "__main__":
    A = input()
    B = input()
    if (len(A) > len(B)):
        print ("GREATER")
    if (len(A) < len(B)):
        print ("LESS")
    if (len(A) == len(B)):
        if (A == B):
            print ("EQUAL")
        for x,y in zip(A, B):
            x = int(x)
            y = int(y)
            if (x > y):
                print ("GREATER")
                break
            if (x < y):
                print ("LESS")
                break
