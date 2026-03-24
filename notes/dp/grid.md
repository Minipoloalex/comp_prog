## DP on grids

### Best path on a grid without a cell
The **best path on a grid without a given grid cell** (considering only movement right and down) will contain certain cells for sure.

Example problem:
https://codeforces.com/contest/2194/problem/E

> ---
>From editorial of that problem
>>Observe that a path does not pass through the cell $(i,j)$ if and only if it contains some cell $(a,b)$ such that either $a<i$ and $b>j$, or $a>i$ and $b<j$. This allows us to consider all such cells $(a,b)$ as possible bypass points.
>>
>

An example, with $X$ as the cell to exclude:

```
----O---
----N---
---X----
OON-----
--------
```

This means that if we want the best grid path (by minimum or maximum), we can use the two DPs: $dpfrom$ and $dpto$, get the values of the best path for a given cell $(i,j)$ using $dpfrom[i][j] + dpto[i][j] - a[i][j]$ and then do prefix max or min on the rows and columns. For a given cell $(i,j)$ that we want to exclude, we can then grab the best solution from the prefix max/min in the neighbor (marked as $N$ in the example). See also my solution to the problem and the editorial explanation.
