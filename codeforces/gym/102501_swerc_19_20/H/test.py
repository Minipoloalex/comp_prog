n = 1000
M = 1 << 40
S = [1611516670]
for i in range(1, n + 1):
    prev = S[i - 1]
    new = (prev + (prev >> 20) + 12345) % M
    S.append(new)

for elem in S:
    print(elem % 2)
