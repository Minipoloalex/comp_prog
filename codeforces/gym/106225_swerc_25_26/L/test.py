n = q = int(5e5)
print(n, q)

# print("a"*n)
for i in range(n):
    print(chr(ord('a') + (i%26)),end="")
print()
for _ in range(q):
    print(1, n-n%26)
