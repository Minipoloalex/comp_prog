fib = [1, 1]

def solve():
    n, k = map(int, input().split())
    for i in range(2, n + 1):
        fib.append(fib[i - 1] + fib[i - 2])
    n -= 1
    while n >= 2:
        # print(f"n = {n}, k = {k}")
        to_test = fib[n - 2]
        if k <= to_test:
            n -= 2
        else:
            n -= 1
            k -= to_test
    assert(n == 1 or n == 0)
    print("N" if n == 0 else "A")
solve()

