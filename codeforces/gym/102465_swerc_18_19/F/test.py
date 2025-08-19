from random import randint
n = int(4e3)
G = int(1e9)
MIN = 0
MAX = int(1e9)

print(n)
for _ in range(n):
    print(randint(MIN, MAX), randint(MIN, MAX), G)
