## Operations
Allows doing point update and range queries in $\mathcal{O}(\log N)$ for any **associative operation**.


## Typical Mistakes
- Sometimes we need to be careful with updates on a Segment Tree, if we want to keep the best value instead of always updating it. For example: https://usaco.org/index.php?page=viewproblem2&cpid=995 and [code](../../usaco/platinum/range_queries/range_queries_with_sweepline/springboards/springboards.cpp).


## Additional Notes
Using a segment tree to replace an order statistics tree may require processing queries offline, since we need to do coordinate compression (probably we could also use a sparse segment tree, which compresses values).

