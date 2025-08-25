import sys
lines = sys.stdin.readlines()

n = int(lines[0])
xs = []
ys = []
for line in lines[1:]:
    x, y = map(int,line.split())
    xs.append(x)
    ys.append(y)

def handle(vec):
    vec.sort()
    add = 0
    p = 0
    for i in range(len(vec)):
        add += vec[i] * i - p
        p += vec[i]
    return add

ans = handle(xs) + handle(ys)
print(ans)
