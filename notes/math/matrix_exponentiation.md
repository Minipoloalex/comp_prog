## Usage
Matrix exponentiation is a tool to **speed up DP with constant space**.

**It can be used when we can combine two small values to form a larger one**. For example, in a directed graph, if we want to get the minimum cost path with exactly $X$ edges:
- We can easily say that the minimum cost of a path between two nodes $i$ and $j$ at distance $2 \cdot X$ is: the minimum cost across every path of length $X$ from $i$ to any node $k$ added with the minimum cost of any path from that node $k$ to the node $j$.
    - We can just minimize across every node $k$ to get the minimum cost from $i$ to $j$ with exactly $2 \cdot X$ edges.

## Complexity
$\mathcal{O}(K^3 \cdot \log{N})$
