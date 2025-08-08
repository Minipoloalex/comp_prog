from random import randint

def first():
    n = int(1e5)
    e = 5 * n
    w = int(1e2)

    def get_rand(src):
        while True:
            v = randint(0, n - 1)
            if v != src:
                return v


    print(n, e)
    for i in range(n):
        for j in range(5):
            print(i, get_rand(i), w)

def second():
    n = int(1e2)
    e = n * n
    w = int(1e2)
    print(n, e)
    for i in range(n):
        for j in range(n):
            if i == j: continue
            print(i, j, w)

first()
