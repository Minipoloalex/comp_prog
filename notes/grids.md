## Grids

### Sizes and Complexity
In a large grid with $X \approx 1e5$ elements, either of its dimensions can be really large (can be a very thin grid). However, the smallest dimension is never very large. It's only $\sqrt{X}$. If we can work on either dimension, this can lead to square-root complexity solutions.

For example, iterating on the pairs of rows (assuming smallest dimension: could require transposing for generality) and then on the columns would lead to $\mathcal{O}(X\sqrt{X})$ (see first example problem).

#### Example problems
1. https://codeforces.com/contest/2159/problem/B: solution is $\mathcal{O}(min(n,m)\cdot n\cdot m)$, which is just $\mathcal{O}(n\cdot m\cdot \sqrt{n \cdot m})$.

