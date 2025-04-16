def valid(x):
    cnts = [0] * 10
    while x:
        d = x % 10
        cnts[d] += 1
        x //= 10

    total = sum(cnts)
    for cnt in cnts:
        if cnt >= total / 2:
            return True
    return False

def get_solution(x, y):
    ans = []
    for i in range(x, y + 1):
        if valid(i):
            ans.append(i)
    return ans

x = 100
y = 10000

with open("odometer.in", "w") as f:
    f.write(f"{x} {y}")

with open("odometer.out", "w") as f:
    sol = get_solution(x, y)
    f.write(f"{len(sol)}\n")
    f.write(str(sol))
