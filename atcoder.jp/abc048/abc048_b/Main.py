if __name__ == "__main__":
    A,B,C = map(int, input().split())
    result = B // C
    result -= A // C
    if (A % C == 0):
        result += 1
    print (result)
