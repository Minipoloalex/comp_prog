from random import randint
MIN = 1
MAX = int(1e9)
n = int(2e5)

print(1)
print(n)
for _ in range(n):
    l = randint(MIN, MAX)
    r = randint(l, MAX)
    print(l, r)
