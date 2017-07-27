import sys
if __name__ == "__main__":

	N,X = map(int, input().split())
	res = 2 * N - 1
	if (X == 1 or X == 2 * N - 1):
		print ("No")
		sys.exit()
	result = [0] * res
	left = X - 1
	result[N-1] = X
	right = X + 1
	left_idx = N - 2
	right_idx = N

	cnt = 0
	while (left > 0 and right < 2 * N):
		if (cnt % 2 == 0):
			result[left_idx] = left
			result[right_idx] = right
		else:
			result[left_idx] = right
			result[right_idx] = left

		left_idx -= 1
		left -= 1

		right_idx += 1
		right += 1

		cnt += 1
	if (left > 0):
		for x in range(left_idx, -1, -1):
			result[x] = left
			left -= 1
		for x in range(right_idx, 2 * N-1):
			result[x] = left
			left -= 1
	if (right < 2 * N):
		for x in range(left_idx, -1, -1):
			result[x] = right
			right += 1
		for x in range(right_idx, 2 * N-1):
			result[x] = right
			right += 1

	print ("Yes")
	for x in result:
		print (x)
