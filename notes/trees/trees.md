## Diameter
To find the diameter of a tree, we can just do 2 DFS's. In one, we will get the farthest node from the current node (0). Then, we can just find the farthest node from that node and their distance is the diameter.

The most distant node of every node in a tree is one of the endpoints of the diameter.
Proof by contradiction: since it's a tree, we know that the nodes connect to the diameter path. If it does and we know our node isn't one endpoint of the diameter, then we also know that it can't be larger than the diameter, so its largest distance is to one of its endpoints.

## DP Solving for All Roots
Usually, in these kinds of problems, we **first compute the result for the subtree only**, using a **bottom-up traversal of the tree** (basically, the answers are propagated from upwards from the leaves). This already obtains the answer for the root of the tree (for the root, the answer for the subtree is simply the answer).

After having the subtree answers, we can **compute the answers also accounting for going up (and not just the subtree)**. We can **propagate the answers downwards from the root**, since already we have the answer for the root. When propagating downwards, $u \rightarrow v$, we likely want to **exclude the answer corresponding to the child $v$ from $u$'s answer $dp[u]$**, so that we can **combine $u$'s answer with $v$'s subtree answer** (to obtain $v$'s answer: $dp[v]$). In some problems, we can may **exclude it manually** (e.g. subtract, divide, modular division...). If that's not possible, we **can also compute the prefix and suffix values for the children of every node**, allowing us to explicitly exclude a specific child's value (aka exclude a child's contribution to $u$'s answer).


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

### Build the Table

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
### Lowest Common Ancestor
https://usaco.guide/CPH.pdf#page=177

#### Method 1

Idea:
- Make nodes $a$ and $b$ be in the same level
- In decreasing order of the number of jumps in $2^k$ (similar to binary search down/up instead of left/right), test if the nodes end up in the same node. We want to find the highest node that the nodes can go up to that is not common to both (then the LCA is just the parent). Note that it needs to be decreasing order and we should move the nodes $a$ and $b$ once we find a valid node (i.e., a node that is not the same for both).

Check https://cses.fi/problemset/result/13181991/ (first submission)

Note that if we do not go in increasing order, there are counterexamples. For instance, needing to go up 2 nodes (LCA is the 3rd node):
We would go up once and then we would not be able to go up more (if in increasing order). The powers of 2 in decreasing order ensures we find what we want.


### Additional notes
We can also include an additional column, to make sure there are no problems: instead of doing just `ceil(log2(n + 1))`, we can just add `+1` at the end.


### Example problems
- Go through k nodes in a successor graph: https://cses.fi/problemset/task/1750
- Determine minimum number of jumps to get from node $a$ to $b$ in a successor graph: https://cses.fi/problemset/task/1160 (similar to A from ONI 2025)


### Distance between two nodes in a tree
Easy to solve using LCA:
$$dist(a, b) = depth[a] + depth[b] - 2 * depth[lca(a, b)]$$
