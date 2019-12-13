n=list(map(int,input()))
n.reverse()
res=0
for i in range(len(n)):
  if i %2==0:
    res+=n[i]
  else:
    res-=n[i]
print(res%11)