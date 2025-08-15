from random import randint
n = int(5e5)
m = int(5e5)
print(n, m)
print("1 " * n)
for _ in range(m):
    l = randint(1, n)
    r = randint(l, n)
    print(l, r)
