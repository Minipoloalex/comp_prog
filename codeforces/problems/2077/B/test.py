x = 0
y = 0

while True:
    n = int(input())
    assert(n < 2**30)
    print((n | x) + (n | y))
