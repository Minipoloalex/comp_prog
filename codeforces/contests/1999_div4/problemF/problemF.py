from math import comb

t = int(input())

MOD = int(1e9 + 7)

# TLE because it tries to do big integer calculations (overflow on comb calculation)

def solve():
    n, k = map(int, input().split())
    count_1s = sum(map(int, input().split()))
    count_0s = n - count_1s

    ans = 0
    for nr1s in range((k + 1) // 2, min(count_1s, k) + 1):
        nr0s = k - nr1s
        contribution = ((comb(count_1s, nr1s) % MOD) * (comb(count_0s, nr0s) % MOD)  % MOD)
        ans = (ans + contribution) % MOD
    print(ans)


while t:
    t -= 1
    solve()

