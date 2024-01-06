import sys
inputs = sys.stdin.read().split()

for i in range(int(inputs[0])):
    d = inputs[i + 1]
    mod = int(1e9 + 7)
    res = (8 * pow(9, int(d) - 1, mod)) % mod
    print(res)
