# Manhattan Distance
Check https://cp-algorithms.com/geometry/manhattan-distance.html

## Manhattan Distance Trick

$$d(p,q) = |x_p - x_q| + |y_p - y_q|$$

We know:
$$|m| + |n| = \text{max}(|m + n|, |m - n|), \quad \forall m, n \in \mathbb{R}$$

We can apply this to our Manhattan distance formula:
 
$$d((x_1, y_1), (x_2, y_2)) = |x_1 - x_2| + |y_1 - y_2| = \text{max}(|(x_1 + y_1) - (x_2 + y_2)|, |(y_1 - x_1) - (y_2 - x_2)|)$$

This is equivalent to the **Chebyshev distance** of the points $(x_1 + y_1, y_1 - x_1)$  and  $(x_2 + y_2, y_2 - x_2)$ . This means that, after applying the transformation:

$$\alpha : (x, y) \to (x + y, y - x)$$

the Manhattan distance between the points $p$ and $q$ turns into the Chebyshev distance between $\alpha(p)$ and $\alpha(q)$.

### Usage
- Maximum Manhattan distance: https://cses.fi/problemset/task/3410
- Manhattan MST (?)
- Other related things: https://codeforces.com/blog/entry/131907

