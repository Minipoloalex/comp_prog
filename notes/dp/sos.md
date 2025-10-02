# SOS DP
- https://usaco.guide/plat/dp-sos
- https://codeforces.com/blog/entry/45223
- https://codeforces.com/blog/entry/105247

We can easily accumulate over submasks and supermasks:
```cpp
for (int i = 0; i < LOG; i++) {
    for (int mask = 0; mask < (1 << LOG); mask++) {
        if (mask & (1 << i)) {
            subsets[mask] += subsets[mask ^ (1 << i)];
            supersets[mask ^ (1 << i)] += supersets[mask];
        }
    }
}
```

How to count **how many $y$ for a given $x$ have $x\ \&\ y \neq 0$:**
- Do $\mathord{\sim} x$ (bitwise-NOT of $x$), and then ask how many submasks of that inverse exist. Those do not share any bit with $x$: correspond to $x\ \&\ y = 0$
- Subtract that result from the total: the result will be those that share at least a bit with $x$.

Problems:
- Direct application: https://codeforces.com/gym/106073/problem/D
- Common idea (all are very similar): https://cses.fi/problemset/task/1654, https://codeforces.com/contest/165/problem/E, https://codeforces.com/contest/383/problem/E
    * The idea of counting how many $y$ for a given $x$ have: $x\ \&\ y \neq 0$
