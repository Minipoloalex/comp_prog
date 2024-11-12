## Fenwick Tree
Check [https://www.youtube.com/watch?v=uSFzHCZ4E-8](https://www.youtube.com/watch?v=uSFzHCZ4E-8) for specifics on how the nodes of the "tree" work and how the calculation of RSQ and the updates work (based on the least significant one).

```cpp
#define LSO(n) ((n) & (-(n)))
```

## Order statistics
### Using policy based data structures

#### Sources and example problems
Example problem solved and explanation of ordered set with order statistics on [https://niteshim111.hashnode.dev/secret-data-structures-of-c-pbds-library](https://niteshim111.hashnode.dev/secret-data-structures-of-c-pbds-library)

Check [Leetcode 3072](https://leetcode.com/problems/distribute-elements-into-two-arrays-ii/): [PBDS solution](../../leetcode/3072/pbds_solution.cpp) and [Fenwick Tree solution](../../leetcode/3072/fenwicktree_solution.cpp).

The fenwick tree solution was modeled as specified on https://github.com/doocs/leetcode/blob/main/solution/3000-3099/3072.Distribute%20Elements%20Into%20Two%20Arrays%20II/README_EN.md (and on the Leetcode problem hints).


## Segment Tree
If the array is not of size $2^k$, we can add elements at the end to make it have the size of the next power of 2. This allows us creating a perfect binary tree. At most, we will have $2*n$ elements, and the complexity will be the same.

### Static RMQ
For the static version, a sparse table DS with $O(N\log{N})$ initialization/pre-processing and $O(1)$ queries is better. The Segment Tree is overkill. 

For dynamic range queries, the Sparse Table will require $O(N\log{N})$ for each update. The Segment Tree is useful if the array is frequently updated (is dynamic).

### Dynamic RMQ
Segment Tree can be applied to all associative operations, e.g.:
- multiplication (normal, modulo, matrix)
- all bitwise operations
- gcd
- ...

#### Point update
Recalculate one node at each level of the tree: $O(\log{N})$

### Get
Note that $[L, R]$ are the indices the node is responsible for, $[i, j]$ is the range we're looking for.

- Completely Outside: Stop recursion and backtrack
$$ i \dots j \dots L \dots R $$
$$ L \dots R \dots i \dots j $$

- Completely Inside: Use the value for result
$$ L \dots i \dots j \dots R $$

- Partially inside/outside: Go deeper in recursive function (call recursively function for both left and right children)
$$ L \dots i \dots R \dots j $$
$$ i \dots L \dots j \dots R $$

#### Complexity reasoning
Since the nodes at a certain level have segments that cannot intersect, only one segment can contain the left index $i$ and only one can contain the right index $i$.

This means that at each level there can be at most 2 nodes in the last situation (partially contained). At most $2 * O(\log{N})$ like this, and at most $4 * O(\log{N})$ nodes visited.

#### Recursing through children
0-indexed:
$$ x: 2 * x + 1$$
$$ x: 2 * x + 2$$
1-indexed:
$$ x: 2 * x$$
$$ x: 2 * x + 1$$

- Going to left child:
    - Left border is the same
    - Right border is the middle of the segment
- Going to right child:
    - Left border is the middle of the segment
    - Right border is the same


Include left but not right border, $[l, r)$:
    $$m = (l + r) / 2$$
    $$child_{left} = [l, m - 1] = [l, m)$$
    $$child_{right} = [m, r - 1] = [m, r)$$

Include both borders, $[l, r]$:
    $$m = (l + r) / 2$$
    $$child_{left} = [l, m]$$
    $$child_{right} = [m + 1, r]$$

#### Sources
https://codeforces.com/edu/course/2


## Disjoin Set Union (DSU)
```cpp
#include <bits/stdc++.h>
using namespace std;

vector<int> parent, rnk;

void make_set(int v) {
    parent[v] = v;
    rnk[v] = 0;
}

int find_set(int v) {
    if (v == parent[v])
        return v;
    return parent[v] = find_set(parent[v]);
}

void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        if (rnk[a] < rnk[b])
            swap(a, b);
        parent[b] = a;
        if (rnk[a] == rnk[b])
            rnk[a]++;
    }
}
```

### Path Compression
```cpp
int find_set(int v) {
    if (v == parent[v]) return v;
    return parent[v] = find_set(parent[v]);
}
```

### Union by Rank
```cpp
void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        if (rnk[a] < rnk[b])
            swap(a, b);
        parent[b] = a;
        if (rnk[a] == rnk[b])
            rnk[a]++;
    }
}
```

### Complexity Reasoning
#### Using just one optimization
Using only one of the 2 presented optimizations will yield an amortized complexity for each of the operations of $\mathcal{O}(\log{n})$.


#### Using both optimizations
Using both will yield an amortized complexity of $\mathcal{O}(\alpha(m, n))$, where $\alpha(m, n)$ is the inverse Ackermann function. $m$ is the number of performed $get$ operations and $n$ is the number of elements.

This function grows very slowly, and for all practical purposes, it can be considered a constant. It even grows slower than $\log^*(n)$, which represents how many times we should take $\log{n}$ to get a value smaller than one. E.g.:
$$2^{65536} = 65536 = 2^{16} = 2^4 = 2^2 = 2 = 1 = 0$$
$$\log^*(2^{65536}) = 6 $$

