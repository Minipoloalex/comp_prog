## DSU

### Interesting patterns

1. Process queries in reverse order ([H.cpp](../../codeforces/gym/105453_grcpc24/H.cpp) from GRCPC 2024)
2. By answering queries offline, sorting queries and edges by weights, we can answer queries in order of their weights, by processing edges as we go through the weights of the queries (e.g. https://usaco.org/index.php?page=viewproblem2&cpid=789)
3. Note that doing something similar to (2), by processing edges in ascending weigths, is similar to Kruskal's algorithm for computing the MST.
