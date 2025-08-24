## Verbal Formula
To compute the size of a **union of multiple sets**, it is necessary to sum the sizes of these sets separately, and then subtract the sizes of all pairwise intersections of the sets, then add back the size of the intersections of triples of the sets, subtract the size of quadruples of the sets, and so on, up to the intersection of all sets.

$K = |S| - 1$, with $|S|$ being the size of the set.

$sign = (-1)^k$

- Add when $|S|$ is **ODD**
- Subtract when $|S|$ is **EVEN**


Note that to compute how many elements **occur in exactly $0$ sets**, we can just start from 0 and invert the subtractions and additions.

Example problems:
- https://cses.fi/problemset/task/2185


PIE can also be used to compute the derangements (since they imply subtracting the union): https://usaco.guide/gold/combo#method-1-principle-of-inclusion-exclusion.


## Mobius

Sources:
- https://usaco.guide/plat/PIE
- https://cp-algorithms.com/combinatorics/inclusion-exclusion.html
