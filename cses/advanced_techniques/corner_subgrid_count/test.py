from random import randint
n = int(3e3)
row = ""
for _ in range(n):
    row += str(randint(0, 1))

print(n)
for _ in range(n):
    print(row)

