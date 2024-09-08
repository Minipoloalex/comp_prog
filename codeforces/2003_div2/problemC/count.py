# from itertools import permutations

res = []
mx = 0
while (1):
    s = input()
    if (s == ""): break
    n = len(s)
    ans = 0
    for i in range(0, n):
        for j in range(i + 1, n):
            if (s[i] == s[j]):
                ans += 1
            else:
                for k in range(i, j):
                    if (k >= n - 1): break
                    if (s[k] != s[k + 1] and (s[k] != s[i] or s[k + 1] != s[j])):
                        ans += 1
                        break
    if ans > mx:
        res.clear()
        res.append(s)
        mx = ans
    elif ans == mx:
        res.append(s)
    # print(s)
    # print(ans)
print(res, mx)
