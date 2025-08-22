## Definitions
### Unimodal functions
Based on https://cp-algorithms.com/num_methods/ternary_search.html

A function $f(x)$ is considered unimodal on an interval $[l, r]$ if one of the following conditions holds:
- The function strictly increases first, reaches a maximum (at a single point or over an interval), and then strictly decreases.
- The function strictly decreases first, reaches a minimum, and then strictly increases.

Both cases can me handled similarly.

### Convex Functions
We can say convex always instead of sometimes concave, since it's the same but flipped. Convex usually refers to a curve with a minimum, and concave to a maximum.

Let's assume that we want to find the local minimum of our function. Then, a function is convex if **consecutive differences are non-decreasing**. In calculus terms, if the derivative of the function is non-decreasing, the function is convex.

Note that this implies that **a convex function is also a unimodal function**.

Basically, we can just show: $$\Delta{f(t)} \ge \Delta{f(t + 1)}$$

With: $\Delta{f(t)} = f(t) - f(t-1)$


We can also define a strictly convex function, although it's not as useful: a function where consecutive differences are increasing (derivative is increasing).

#### Properties
- The sum of convex functions is also convex. Examples of usage:
    * https://usaco.org/index.php?page=viewproblem2&cpid=1355, https://usaco.guide/gold/ternary-search#example---haybale-distribution
    * https://codeforces.com/problemset/problem/2063/D
- A function $C(y)$ is convex if its first derivative, $C'(y)$, is non-decreasing.
- A function $C(y)$ is concave if its first derivative, $C'(y)$, is non-increasing.
- Check: [codeforces/problems/427/E/notes.md](../../codeforces/problems/427/E/notes.md) on an example of how to prove that a function is convex. We can show that the **first derivative is non-decreasing**, or that the second derivative is non-negative.
- The maximum of two convex functions (have a minimum) is also convex. The minimum of two concave functions (have a maximum) is also concave.
- The sum of two **strictly** convex functions is always **strictly** convex.
- We can't tell anything from the sum of a convex and a concave function.

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

To better measure the number of operations, you can also 
$\mathcal{O}(\log_{3/2}(\frac{n}{\epsilon})) = \mathcal{O}(\log_{1.5}(\frac{n}{\epsilon}))$

## Binary Search (For Ternary Search)
```cpp
int lo = 0, hi = n - 1;
while (lo < hi) {
    int m = lo + (hi - lo) / 2;
    if (value(m) < value(m + 1)) {  // here, we compare m and m + 1
        hi = m;
    }
    else {
        lo = m + 1;
    }
}
```

## General considerations
> A function is unimodal if it strictly decreases first, then reaches a minimum, then strictly increases (for the minimum case).

We are very specific about the function having to strictly increase and decrease. This is because **we can only allow our function to be flat at the minimum!** If we have a flat section anywhere else, it's possible that our ternary search ends up eliminating the wrong section.

## Example problems
Check [USACO ternary search](https://usaco.guide/gold/ternary-search).
