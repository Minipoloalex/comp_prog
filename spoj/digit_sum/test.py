def cnt(x):
    sm = 0
    while x:
        d = x % 10
        sm += d
        x //= 10
    return sm

mn = 1
mx = 11

total = 0
for i in range(mn, mx + 1):
    total += cnt(i)
print(total)
