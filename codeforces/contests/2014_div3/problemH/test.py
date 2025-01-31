from random import randint
t = 1
n = int(2e5)
mx = int(1e6)
q = 20
print(t)
for _ in range(t):
    print(n, q)
    s = ""
    for _ in range(n):
        s += str(randint(1, mx)) + " "
    print(s)
    for _ in range(q):
        print("1 100")
