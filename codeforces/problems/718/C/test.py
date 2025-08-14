from random import randint
n = int(1e5)
m = int(1e5)
MAX = int(1e9)

print(n, m)
print(f" {MAX}" * n)
for _ in range(m - 1):
    l = randint(1, n)
    r = randint(l, MAX)
    print(1, l, r, MAX)

print(2, 1, n)
