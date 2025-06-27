## Unimodal functions
Based on https://cp-algorithms.com/num_methods/ternary_search.html

A function $f(x)$ is considered unimodal on an interval $[l, r]$ if:
- The function strictly increases first, reaches a maximum (at a single point or over an interval), and then strictly decreases.
- The function strictly decreases first, reaches a minimum, and then strictly increases.

Both cases can me handled similarly.

## Ternany Search
The objective is to find the maximum (for case 1 as in above) of an unimodal function.

Given two points $m_1$ and $m_2$, we make a decision to cut some part:
- $f(m_1) < f(m_2)$: eliminate $[l,m1)$
- $f(m_1) > f(m_2)$: eliminate $(m2, r]$
- $f(m_1) = f(m_2)$: eliminate $[l,m1)$ and $(m2, r]$. This can be included in one of the other cases for simplicity. It also assumes strictly increasing/decreasing ($m_1$ and $m_2$ cannot have "the same exact value" without it having changed in the middle or it being the answer)

## Choosing $m_1$ and $m_2$
$$m_1 = l + \frac{(r - l)}{3}$$

$$m_2 = r - \frac{(r - l)}{3}$$


To break from the ternary search:

- For double values: $r - l \le \epsilon$
- For integer values: $(r - l) < 3$. Here, we also need to check the values that are left $(l, l + 1, \dots, r)$ to find the one that corresponds to the maximum. Actually, binary search would work more efficiently for this (less evaluations of $f(x)$), since we can just find the first point at which the function becomes strictly decreasing/increasing (we can use $m$ and $m + 1$). In the case of floating point values, binary search can be problematic because of the loss of precision, so ternary search is preferred.

## Complexity
Complexity is obviously logarithmic, but here it is:
$$T(n) = T({2n}/{3}) + O(1) = \Theta(\log n)$$

With a fixed error margin $\epsilon$, the complexity becomes:
$\mathcal{O}(\log(\frac{n}{\epsilon}))$

