# SOS DP
- https://usaco.guide/plat/dp-sos
- https://codeforces.com/blog/entry/45223
- https://codeforces.com/blog/entry/105247


## Basic Usage
$$x\ \&\ y = x$$
$$x\ |\ y = x$$

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

### Slightly less basic usage
$$x\ \&\ y = 0$$
$$x\ \&\ y \neq 0$$
How to count **how many $y$ for a given $x$ have $x\ \&\ y \neq 0$:**
- Do $\mathord{\sim} x$ (bitwise-NOT of $x$), and then ask how many submasks of that inverse exist. Those do not share any bit with $x$: correspond to $x\ \&\ y = 0$.
- Subtract that result from the total: the result will be those that share at least a bit with $x$.

## Going backwards
Check out problems in the last point of the suggestions.

For example, the problem of finding how many subsets of elements of a specific array $a$ respect the condition $a_{i_1}\ \&\ a_{i_2} \cdots\ \&\ a_{i_k} = k$ (we can answer queries over $k$).

- We know that they must have at least the bits in $k$, so we can start by including in every mask $m$ numbers from the array $a$ that are supermasks of that mask $m$.
- This will give us counts of numbers that may be used. We can $2^{cnt}$ for every mask to get the number of subsets.
- But a specific subset may exceed the objective value $k$, so we need to exclude those subsets. We can do this using ***backwards* SOS**. For every mask, we want to remove the subset counts from supermasks of it, since these correspond to subsets that will lead to a bitwise-AND $> k$.
- Actually, we don't need to think of ***backwards* SOS** as a new thing. We can just interpret it as being a **sum of negative values**, which makes it very similar to basic SOS. Here, for a specific mask $m$ we want to exclude (instead of include, so we use subtraction instead of addition) the subset counts from supermasks of $m$. These correspond to cases of subsets where the bitwise-AND is larger than $k$.


## Problems:
- Direct application: https://codeforces.com/gym/106073/problem/D
- Common idea (all are very similar): https://cses.fi/problemset/task/1654, https://codeforces.com/contest/165/problem/E, https://codeforces.com/contest/383/problem/E
    * The idea of counting how many $y$ for a given $x$ have: $x\ \&\ y \neq 0$
- Idea of going backwards after making some operation on the SOS array: https://codeforces.com/contest/449/problem/D, https://codeforces.com/gym/106073/problem/H.

