## Diameter
To find the diameter of a tree, we can just do 2 DFS's. In one, we will get the farthest node from the current node (0). Then, we can just find the farthest node from that node and their distance is the diameter.

## Binary Jumping

Check the link: https://usaco.guide/plat/binary-jump?lang=cpp

Example:

![alt text](images/image.png)

The table represents the `2^k`-th ancestor of node `i`.

| `i` | `2^0` (k=0) | `2^1` (k=1) | `2^2` (k=2) |
|-----|-------------|-------------|-------------|
| 0   | -1          | -1          | -1          |
| 1   | 0           | -1          | -1          |
| 2   | 1           | 0           | -1          |
| 3   | 2           | 1           | -1          |
| 4   | 3           | 2           | 0           |

## Build the Table

The way to compute is simple:
- In ascending order of $k$, compute this for every node $i$: $$\texttt{up}[\texttt{i}][\texttt{k}] = \texttt{up}[\texttt{up}[\texttt{i}][\texttt{k}-1]][\texttt{k}-1], \\\textit{if}\ \ \texttt{up}[\texttt{i}][\texttt{k}-1] \neq -1$$

If we always use $0$ instead of $-1$, then we don't need the $\textit{if}$.

Example code (not my implementation, from USACO): [binary_jumping.cpp](src/binary_jumping.cpp). Also check https://cses.fi/problemset/task/1687 (my code).

### Find $k$-th parent

To jump $k$ nodes up in the tree, we can just iterate over each bit in $k$ and, if it's active, we go through the parent corresponding to that number.

```cpp
if ((k & (1 << pw))) {
    x = up[x][pw];
    if (x == -1) {
        break;  // stop when we're past the root
    }
}
```

### Additional notes
We can also include an additional column, to make sure there are no problems: instead of doing just `ceil(log2(n + 1))`, we can just add `+1` at the end.
