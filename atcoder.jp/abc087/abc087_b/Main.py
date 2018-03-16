if __name__ == "__main__":
    A = int(input())
    B = int(input())    
    C = int(input())        
    X = int(input())
    result = 0
    for a in range(A + 1):
        for b in range(B + 1):
            for c in range(C + 1):
                cost = a * 500 + b * 100 + c * 50
                if cost == X:
                    result += 1
    print (result)

