## Efficiency
- **Monotonic slopes and queries**: $\mathcal{O}(N)$ using a deque
- **Monotonic slopes**: $\mathcal{O}(N \cdot \log{N})$ using binary search on the current lines to answer queries
- **No restrictions**: $\mathcal{O}(N \cdot \log{N})$ using a multiset (slower than simple binary search), or using a Li Chao Tree.

## Implementation and Code
Check [monotonic_dp_hull.hpp](monotonic_dp_hull.hpp), taken from: https://usaco.guide/problems/cses-2087-houses-and-schools/solution.

This implementation uses the abstraction from the cp-algorithms: for $y=k\cdot x + b$, it uses $k$ and $b$ space ($k$ is $x$-axis, while $b$ is $y$-axis).

## References
- https://cp-algorithms.com/geometry/convex_hull_trick.html
- https://usaco.guide/plat/convex-hull-trick
