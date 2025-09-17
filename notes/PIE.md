# PIE
## Verbal Formula
To compute the size of a **union of multiple sets**, it is necessary to sum the sizes of these sets separately, and then subtract the sizes of all pairwise intersections of the sets, then add back the size of the intersections of triples of the sets, subtract the size of quadruples of the sets, and so on, up to the intersection of all sets.

$K = |S| - 1$, with $|S|$ being the size of the set.

$sign = (-1)^k$

- Add when $|S|$ is **ODD**
- Subtract when $|S|$ is **EVEN**

## Mathematical formula

### Size of the Union of sets
The mathematical formula is:

$$|A_1 \cup A_2 \cup \cdots \cup A_n| = \left|\bigcup_{i=1}^n A_i \right| = \sum_{\emptyset \neq J\subseteq \{1,2,\ldots ,n\}} (-1)^{|J|-1}{\Biggl |}\bigcap_{j\in J}A_{j}{\Biggr |}$$

In code, we do:
```cpp
for (int mask = 1; mask < (1 << n); mask++) {
    // ...
    int has_odd_sz = __builtin_parity(mask);
    if (has_odd_sz) {
        ans += ...
    }
    else {
        ans -= ...
    }
}
```

### Inverse Problem: Intersection of NOTs

Note that to compute how many elements **occur in exactly $0$ sets** (i.e., appear in no sets), we can just start from 0 and invert the subtractions and additions. The formula is:

$$\left|\overline{A_1} \cap \overline{A_2} \cap \cdots \cap \overline{A_n}\right| = \left|\bigcap_{i=1}^n \overline{A_i}\right|=\sum_{m=0}^n (-1)^m \sum_{|X|=m} \left|\bigcap_{i\in X} A_{i}\right|$$

Note how this formula is slightly adapted, where instead of going per-set, we are thinking per-size.

- In the formula above, we **fix a size/number of sets $m$ to handle**, with the sign depending on the parity of that size $m$.
- Then, we handle each possible set of $m$ chosen $A_i$'s (represented by $X$). Here, for each set, we are computing the size of at least that set (the intersection of all $A_i$ in the set) and not the set of only $X$. For example, we calculate $A_1 \cap A_2 \cap A_3$ and not $A_1 \cap A_2 \cap A_3 \cap \overline{A_4} \cap \overline{A_5}$.

In the code, we can include the universe set (start from zero instead of one).

```cpp
// Compute the union
for (int i = 1; i < (1 << n); i++)

// Compute the intersection of the "nots" (start is 0 to include all universe initially, then subtract union)
for (int i = 0; i < (1 << n); i++)
```

### Generalized PIE: size of the union of exactly $r$ sets
Explanation for https://cp-algorithms.com/combinatorics/inclusion-exclusion.html#generalization-for-calculating-number-of-elements-in-exactly-r-sets.

Previously, we saw how to compute the size of the **Union** and in **exactly $0$ sets**. We can generalize this to exactly $r$ sets.

The main formula is:
$$\left|\bigcup_{|B|=r}\left[\bigcap_{i \in B} A_i \cap \bigcap_{j \not\in B} \overline{A_j}\right]\right|=\sum_{m=r}^n (-1)^{m-r}\dbinom{m}{r} \sum_{|X|=m} \left|\bigcap_{i \in X} A_{i}\right|$$


Now, we need to show why it's true. Conventions used:
- $[n]=\{1,\dots,n\}$
- $B\subseteq[n]$, with $|B|=r$
- $C=\bigcap_{i\in B}A_i$

First, we can consider each particular $B$ independently, since different sets $B$ do not intersect each other (meaning we can just add them together).

The main idea is that we need to do basic PIE over the new "subset of elements" (new "universe"): $$C = \bigcap_{i \in B} A_i$$

Basically, we need to view this as the new universe and do the intersection of the nots in this universe.

For each $B$, we want to get:

$$
\left|C\setminus \bigcup_{j\notin B}A_j\right|
\;=\;
|C|-\left|\,C\cap \bigcup_{j\notin B}A_j\right|
$$

We can do basic PIE, but need to take into account the new universe we're in: $C$. The result is:
$$
\left|\,C\cap \bigcup_{j\notin B}A_j\right|
=
\sum_{\emptyset\neq S\subseteq [n]\setminus B}
(-1)^{|S|+1}\;
\left|\,C\cap \bigcap_{j\in S}A_j\right|
$$

Or instead, if we already handle the subtraction implicitly:
$$
\left|C\setminus \bigcup_{j\notin B}A_j\right|
=
\sum_{S\subseteq [n]\setminus B}
(-1)^{|S|}\;
\left|\,C\cap \bigcap_{j\in S}A_j\right|
$$

With $X=B\cup S$, and going back to the definition of $C$, we have $m = |X| = r + |S|$, and the formula would be:

$$
\left|\bigcap_{i \in B} A_i \cap \bigcap_{j \not \in B} \overline{A_j}\right|
=\sum_{\substack{X\subseteq [n]\\ B \subseteq X}}
(-1)^{|X|-r}\;
\left|\bigcap_{i\in X} A_{i}\right|.
$$

After factoring over the size $m = |X|$, we get:

$$\left|\bigcap_{i \in B} A_i \cap \bigcap_{j \not \in B} \overline{A_j}\right|=\sum_{m=r}^{n} (-1)^{m-r} \sum_{\substack{|X|=m \newline B \subseteq X}}\left|\bigcap_{i\in X} A_{i}\right|$$

Going back to the original formula, where we need to consider multiple sets $B$, we can derive the contribution of a specific set of size $m \ge r$. Each set of size $m$ will appear $\dbinom{m}{r}$ times, since we need to choose which elements are in $B$. Note how the definition means all sets of size $m$ have this factor. The same happens with the $(-1)^{m-r}$ factor. 

This means that for each size $m$, we can factor these two components and sum the contributions of each set with $m$ elements (like we did above). In fact, in the formula above, a specific set $X$ appears with respect to multiple $B$ sets, but its contribution will be the same for all of them (note how $r$ is a constant so $m - r$ doesn't change). This allows us to factor the number of its appearances, which is $\dbinom{m}{r}$.

The formula simplifies to the original we wanted to show:

$$\left|\bigcup_{|B|=r}\left[\bigcap_{i \in B} A_i \cap \bigcap_{j \not\in B} \overline{A_j}\right]\right|=\sum_{m=r}^n (-1)^{m-r}\dbinom{m}{r} \sum_{|X|=m} \left|\bigcap_{i \in X} A_{i}\right|$$

## Use cases

PIE can also be used to compute the derangements (since they imply subtracting the union): https://usaco.guide/gold/combo#method-1-principle-of-inclusion-exclusion.


Example problems:
- https://cses.fi/problemset/task/2185
- https://atcoder.jp/contests/abc423/tasks/abc423_f



## Mobius

Sources:
- https://usaco.guide/plat/PIE
- https://cp-algorithms.com/combinatorics/inclusion-exclusion.html
