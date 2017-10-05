if __name__ == "__main__":
    a,b = map(int, input().split())
    if a >= 3 and a % 3 == 0:
        print ("Possible")
        exit()
    if b >= 3 and b % 3 == 0:
        print ("Possible")
        exit()
    if (a + b) >= 3 and (a + b) % 3 == 0:
        print ("Possible")
        exit()
    print ("Impossible")
