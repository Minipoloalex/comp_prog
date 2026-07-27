
def val(n, a):
    # return (n-a)*(n-a)/2 + (n-a)/2 + n - a + 1
    b = n - a

    i = 2
    j = 1
    cur = -1
    ans = 0
    while cur < b:
        print(n,a)
        ans += n // i * j * j
        cur += n // i
        i *= 2
        j *= 2
    return ans
    # return n // 2 + n // 4 * 2 * 2 + n // 8 * 4 * 4 + n // 16 * 8 * 8  + n // 32 * 16 * 16

def limit(n, a):
    return n*n/a

for n in range(2, 40):
    for a in range(3, n+1):
        assert val(n, a) <= limit(n, a), f"Not valid for case: n={n}, a={a}, cost={val(n, a)}, limit={limit(n, a)}"
