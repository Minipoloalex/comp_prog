from math import sqrt

# l = 1000000000
# r = 9999999999
# ans = []
# for i in range(1, 100000):
#     v = i * i
#     if v in range(l, r):
#         ans.append(v)
# print(len(ans))


import itertools

nrs = [0, 0, 1, 6, 9]
n = len(nrs)
ans = set()
for c in itertools.permutations(range(n), n):
    nr = 0
    for v in c:
        val = nrs[v]
        nr *= 10
        nr += val

    sq = int(sqrt(nr))
    if sq * sq == nr:
        ans.add(nr)

print(ans)
