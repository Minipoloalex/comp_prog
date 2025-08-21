from random import randint

n = int(2e5)
MAX_V = int(1e6)
v = randint(1, MAX_V)
MIN_TI = 1
MAX_TI = int(1e9)

MIN_AI = int(-1e9)
MAX_AI = int(1e9)

print(n, v)
last = MIN_TI
for _ in range(n):
    v = randint(last, MAX_AI)
    print(v, end=" ")
    last = v
print()
for _ in range(n):
    print(randint(MIN_AI, MAX_AI), end=" ")
print()
