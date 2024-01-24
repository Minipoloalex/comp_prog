import sys

# big ints required
query = int(input())

cat = [1]

for i in range(1, query + 10):
    n = i - 1
    cat.append((4 * n + 2) * cat[n] // (n + 2))

res = 0
for k in range(0, query + 1):
    res += cat[k] * cat[query - k]
print(res)
