## Operations
Allows doing point update and range queries in $\mathcal{O}(\log N)$ for any **associative operation**.

Any interval can be decomposed into $\mathcal{O}(N\cdot \log{N})$ nodes in the segment tree. Specifically, we can prove it is decomposed in at most $4$ nodes at each level in the segment tree (and there are $\log{N}$ levels).

### O(N) memory in each node
We can keep more information in each node, similar to a a merge-sort way. In fact, a **Merge-Sort Tree** is just a Segment Tree that keeps the entire list of elements in each node (can use any kind of data structure).

## Typical Mistakes
- Sometimes we need to be careful with updates on a Segment Tree, if we want to keep the best value instead of always updating it. For example: https://usaco.org/index.php?page=viewproblem2&cpid=995 and [code](../../usaco/platinum/range_queries/range_queries_with_sweepline/springboards/springboards.cpp).


## Additional Notes
Using a segment tree to replace an order statistics tree may require processing queries offline, since we need to do coordinate compression (probably we could also use a sparse segment tree, which compresses values).

