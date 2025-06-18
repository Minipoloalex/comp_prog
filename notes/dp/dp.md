## Bitmask DP
https://usaco.guide/gold/dp-bitmasks

1. Submasks Enumeration: For each mask, enumerate all of its submasks. DP application, based on https://usaco.guide/gold/dp-bitmasks#merging-subsets.

It may seem like there are $\mathcal{O}(2^N)$ submasks for each mask, in average. However, we can analyse it like this to prove the overall complexity is actually not $\mathcal{O}(2^N \cdot 2^N) = \mathcal{O}(4^N)$ and instead $\mathcal{O}(3^N)$.
 
Count the number of ordered pairs $(T, S)$ where $T \subset S$. Instead of counting directly, notice that each element $x$ is either:

- In $T$ and $S$
- In neither
- In $S$ but not in $T$.

If $x$ is in $T$ but not in $S$, $T$ isn't a valid subset.

Given that each element can be in three possible states, our overall complexity is actually $\mathcal{O}(3^N)$.


Trick for implementation:
```cpp
for (int m = 0; m < (1 << n); ++m)
    for (int s = m; s; s = (s-1) & m)
        doSomething();
```

From USACO:
When we subtract $1$ from $\texttt{submask}$, its rightmost bit flips to a $0$ and all bits to the right of it will become $1$. Applying the bitwise AND with $\texttt{mask}$ removes all extra bits not in $\texttt{mask}$. From this process, we can get all strict subsets in increasing order by calculating $\texttt{mask} \oplus \texttt{submask}$, which does set subtraction.
```cpp
for (int mask = 0; mask < (1 << n); mask++) {
	for (int submask = mask; submask != 0; submask = (submask - 1) & mask) {
		int subset = mask ^ submask;
		// do whatever you need to do here
	}
}
```

## Range DP

Typically $N = 500$, and solution is $\mathcal{O}(N^3)$. The $DP$ array is based on subarray intervals: $DP[i][j]$, with the transition being commonly $\mathcal{O}(N)$.

A **common pattern** is trying to match the first value/character (possibly) with each value/character inside the interval $[i,j]$ from the $DP$ state. Then, handling the interval in the middle $[i+1,idx-1]$ and the interval after $[idx+1,j]$. See example problems.

### Example problems:
- https://saco-evaluator.org.za/cms/sapo2015z/tasks/jazz/description
- https://codeforces.com/problemset/problem/607/B

