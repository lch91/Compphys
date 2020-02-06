from scitools.std import *

n = 10
A = 2*eye(n)

for i in range(n):
	for j in range(n):
		if i-1 == j or i+1 == j:
			A[i-1,j] = -1
			
			#A[i+1,j] = -1
			
print A
