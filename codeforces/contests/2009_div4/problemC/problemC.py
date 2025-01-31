from math import ceil
t = int(input())
for _ in range(t):
    x, y, k = list(map(int, input().split()))
    hor = ceil(x / k)
    vert = ceil(y / k)
    if hor == vert or hor == vert + 1:
        ans = hor + vert
    elif hor > vert:
        ans = hor + vert + (hor - vert - 1)
    else:
        assert(hor < vert)
        ans = vert + hor + vert - hor
    print(ans)
