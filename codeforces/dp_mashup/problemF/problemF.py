from math import comb

n, k = map(int, input().split())

ans = 1
if k >= 2:
    ans += comb(n, 2)
if k >= 3:
    ans += 2 * comb(n, 3)   # derangements manually calculated
if k >= 4:
    aux = comb(n, 4)
    ans += 9 * aux  # derangements manually calculated

print(ans)
