n = int(2e5)
t = 2
print(t)
print(n)
colors = " ".join(str(1) for i in range(n))
print(colors)
for i in range(1, n):
    print(i, i + 1)


print(n)
colors = "2 " + " ".join(str(1) for i in range(n - 1))
print(colors)
for i in range(2, n + 1):
    print(1, i)

# int(2e5 - 1) * int(2e5 - 2) / 2
