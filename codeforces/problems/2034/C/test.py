from random import choice
n = 1000
m = 1000

print(1)
print(n, m)
for r in range(n):
    for c in range(m):
        print(choice("LURD?"), end="")
    print()
