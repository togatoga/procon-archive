import sys
n=int(input())
for i in range(n+10):
   if i*i > n:
      print(i-1)
      break
      
