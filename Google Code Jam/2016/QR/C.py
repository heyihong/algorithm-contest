import sys

def get_divisor_slow(n):
	i = 2
	while i * i <= n:
		if n % i == 0:
			return i 
		i += 1
	return n 

small_primes = []

for i in range(2, 1 << 8):
	if get_divisor_slow(i) == i:
		small_primes.append(i)

def get_divisor_fast(n):
	for small_prime in small_primes:
		if n % small_prime == 0:
			return small_prime
	return n

def is_legitimate(n, l, get_divisor):
	result = []
	div = get_divisor(n)
	if div == n or (n & 1) == 0 or (n >> (l - 1)) != 1:
		return None 
	result.append(div)
	for b in range(3, 11):
		x = n
		p = 1
		num = 0
		while x > 0:
			if (x & 1) == 1:
				num += p	
			p *= b
			x >>= 1
		div = get_divisor(num)
		if div == num:
			return None
		result.append(div)
	return result

def solve(l, j):
	i = 1 << (l - 1)
	while j > 0: 
		result = is_legitimate(i, l, get_divisor_fast)
		if result:
			print bin(i)[2:],
			for idx in range(len(result)):
				if idx == len(result) - 1:
					print result[idx]
				else:
					print result[idx],
			j -= 1
		i += 1

if __name__ == "__main__":
	lines = sys.stdin.readlines()
	test_cases = int(lines[0])
	for tc in range(1, test_cases + 1):
		print "Case #%d:" % (tc)
		sp = lines[tc].split(' ')
		l = int(sp[0])
		j = int(sp[1])
		solve(l, j)
