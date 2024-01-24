import sys

# big ints required
inputs = sys.stdin.readlines()

fst = int(inputs[0])
cat = [1]

for i in range(1, 5001):
    n = i - 1
    cat.append((4 * n + 2) * cat[n] // (n + 2))

for query in inputs[1:]:
    n = int(query)
    print(cat[n])

