## Problem-specific function
- The number of trips required for criminals to the left of $y$ is $N_L(y) = \lceil n(y) / m \rceil$
- The number of trips for criminals to the right of or at $y$ is $N_R(y) = \lceil (n - n(y)) / m \rceil$.
---
- The endpoints for the left trips are ${x_0, x_m, x_{2m}, \dots}$.
- The endpoints for the right trips are ${x_{n-1}, x_{n-1-m}, \dots}$.
---
The total cost $C(y)$ is the sum of distances to these endpoints:

$C(y) = 2 \left( \sum_{i=0}^{N_L(y)-1} (y - x_{i \cdot m}) + \sum_{j=0}^{N_R(y)-1} (x_{n-1-j \cdot m} - y) \right)$

---
## Proof of Convexity for $C(y)$
**To prove that $C(y)$ is convex, we can show that its first derivative, $C'(y)$, is a non-decreasing function.** The same could be said for a concave: the first derivative needs to be non-increasing.

$C'(y) = \frac{dC}{dy} = 2 \left( \sum_{i=0}^{N_L(y)-1} (1) + \sum_{j=0}^{N_R(y)-1} (-1) \right)$

$C'(y) = 2 \left( N_L(y) - N_R(y) \right)$

---

Now, let's see how $C'(y)$ behaves as $y$ increases:

- As $y$ increases, the number of criminals to its left, $n(y)$, either stays the same or increases.

- Therefore, $N_L(y) = \lceil n(y) / m \rceil$ is a non-decreasing function of $y$.

- Consequently, $n - n(y)$ is a non-increasing function, which means $N_R(y) = \lceil (n - n(y)) / m \rceil$ is a non-increasing function of $y$.

Since $N_L(y)$ is non-decreasing and $N_R(y)$ is non-increasing, their difference ($N_L(y) - N_R(y)$) must be non-decreasing.

**By definition, a function whose first derivative is non-decreasing is a convex function. This formally proves that the underlying cost function C(y) is convex.**

This mathematical property is inherent to the problem's cost structure and holds true for all indices k \in [0, n-1]. It is not an artifact of sampling at multiples of m.
