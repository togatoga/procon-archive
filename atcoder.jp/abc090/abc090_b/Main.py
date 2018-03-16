def is_palindromic(x):
    s = str(x)
    left = 0
    right = len(s) - 1
    while (left < right):
        if (s[left] != s[right]):
            return False
        left += 1
        right -= 1
    return True
    
if __name__ == "__main__":
    A,B = map(int, input().split())
    result = 0
    for x in range(A, B + 1):
        if is_palindromic(x):
            result += 1
    print (result)