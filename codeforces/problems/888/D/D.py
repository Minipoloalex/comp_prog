from math import comb, factorial
n, k = map(int, input().split())

mults = [1, 0, 1, 2, 9]
ans = 1
while k > 1:
    ans += comb(n, k) * mults[k]
    k -= 1
print(ans)
