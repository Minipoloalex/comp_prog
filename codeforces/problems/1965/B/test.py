from random import randint
t = 1000
MAX_N = int(1e6)
print(t)
for _ in range(t):
    n = randint(2, MAX_N)
    k = randint(1, n)
    print(n, k)
