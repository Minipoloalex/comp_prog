n = 20
m = 20
x = 1
g = [[0 for _ in range(n)] for __ in range(m)]
g[0][0] = 1

print(n, m, 1)
for i in range(n):
    for j in range(m):
        print(g[i][j], end=" ")
    print()
