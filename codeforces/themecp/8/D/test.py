import itertools
mn = -3
mx = 4

start = [-2,-2,2,2]
# start = [-3,-2,-1,0,1,2,3,4]
n = len(start)

def agg(ids, lst):
    sm = 0
    mult = 1
    for i in ids:
        sm += lst[i]
        mult *= lst[i]
    return sm, mult

def f(cur):
    possible = True
    for comb in itertools.combinations(range(n), n // 2):
        other = []
        for i in range(n):
            if i not in comb:
                other.append(i)

        sm1, mult1 = agg(comb, cur)
        sm2, mult2 = agg(other, cur)
        if sm1 != mult2 or sm2 != mult1:
            possible = False
            break

    ans = 0
    if not possible:
        ans = int(1e9)
    else:
        for i in range(len(start)):
            ans += abs(start[i] - cur[i])
    return ans

ans = int(1e9)
res = []
def choose(i, cur):
    global ans, res
    if i == n:
        cur_ans = f(cur)
        if cur_ans < ans:
            ans = cur_ans
            res = cur.copy()
        return
    for v in range(mn, mx + 1):
        cur.append(v)
        choose(i + 1, cur)
        cur.pop()


choose(0, [])
print(ans)
print(res)
