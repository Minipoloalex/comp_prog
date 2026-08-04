## "Propagate" DP


A type of DP with 2 states over the same dimension where we want to propagate values to subset or superset ranges.

>Aside (non-important):
>
>>They called it Range DP in the first example problem editorial, but we use that name here for the harder and more interesting Range DP ([range.md](range.md)). I use the name "Propagate" here because I don't know a better name for it.
>---

### Explanation (based on an example)
For example (similar to the second part of https://codeforces.com/contest/2159/problem/B):

We have several intervals $[i,j]$ of a dimension $N$ with specific values $v$ that are applicable not just to the exact endpoints, but also to the points within the intervals. For each point in $N$, we want to find the minimum value of an interval that contains it.

This would be the brute force solution. It can iterate a lot of times over each point, since we iterate over the points in the intervals.

```cpp
vector<int> ans(N, INT_MAX);
for (auto &[i, j, v]: ivals) {
    for (int u = i; u <= j; u++) {
        ans[i] = min(ans[i], v);
    }
}
```

We can instead do this using the intended DP solution.

```cpp
vector<int> ans(N, INT_MAX);
vector<vector<int>> dp(n, vector<int>(n, INT_MAX));

for (int len = n; len >= 2; len--) {
    for (int i = 0; i + len - 1 < n; i++) {
        int j = i + len - 1;
        dp[i][j-1] = min(dp[i][j-1], dp[i][j]);
        dp[i+1][j] = min(dp[i+1][j], dp[i][j]);
    }
}

// Then, the interval [i,i] contains the solution for point i
for (int i = 0; i < n; i++) {
    ans[i] = dp[i][i];
}
```

The order is important, so that when handling interval $[i,j]$, all intervals above it (its superset intervals, which are larger) have been handled. Processing first larger intervals ensures that their values get pushed by smaller intervals that contain them (that can use those values).

The transitions lead to propagation from $[i,j]$ to all intervals (and points) inside it:
$$
dp[i][j-1] = min(dp[i][j-1], dp[i][j])
\\
dp[i+1][j] = min(dp[i+1][j], dp[i][j])
$$

So, at each step, the value $dp[i][j]$ contains the values from all intervals that contain it (i.e., its superset intervals).

### Example problems:
1. https://codeforces.com/contest/2159/problem/B

