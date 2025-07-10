# CSES
## Introductory
- Apple Division: classic **Minimum Subset Sum Difference** NP-hard problem. Brute force $\mathcal{O}(2^N)$


## Sorting and Searching
- Nearest Smaller Values: for each index, find nearest position to left having a smaller value - **Classic monotonic stack**
- Playlist: **two pointers** with set
- Subarray Distinct Values: **sliding window** on distinct values, with a map
- Maximum subarray sum 2: **sliding window on prefix sums** to find valid minimum for max subarray sum
- Missing coin sum: simple **greedy with sorting**

## Dynamic Programming
- Minimal grid path: instead of a shortest path in the grid, we want the **lexicographically shortest string of the path**. This requires looking for the next character at each step, based on the possible positions (with best prefix) from the previous step.
- Mountain range: Next greater to build a graph (monotonic stack), then just $DP$ to find the longest path distance in the graph.
- Increasing subsequences 2: DP thought process for subsequences, based on **bucketing previous results**. Requires range queries and coordinate compression.

## Graph Algorithms
- Counting Rooms: counting **connected components** - **DFS**
- Labyrinth: find **shortest path with unweighted edges** from start to end in a labyrinth and specify the path - **BFS**
- Building Roads: number of **connected components** and which edges to add to modify to only 1 CC - **DFS**
- Message Route: **shortest path with unweighted edges** between two nodes and specify the path - **BFS**
- Round trip: find any cycle in an undirected graph
- Monsters: **shortest path with unweighted edges** from start to end in a labyrinth and specify the path. Also, avoid monsters - **BFS** from multiple sources
- Shortest Routes 1: simplest **Dijkstra**
- Shortest Routes 2: simplest **Floyd-Warshall**
- Flight Discount: example of **adapting Dijkstra with flags**: distance array with >1D. Another possible solution is more ad-hoc (solution 1 from https://usaco.guide/problems/cses-1195-flight-discount/solution)
- Round trip 2: find any cycle in a directed graph
- Course Schedule: simplest **topological sort**
- Longest Flight Route: simple **DP in a DAG**: find longest path in a DAG
- Game Routes: simple **DP in a DAG**: find number of ways to go from $a$ to $b$
- Road Reparation: simplest **MST**: using Kruskal or Prim
- Road Construction: classic **DSU to get connected components** number and max size.
- Planets queries 1: go through k nodes in a **successor graph**: simple **binary lifting**
- Planets queries 2: determine minimum number of jumps to get from node $a$ to $b$ in a **successor graph**: **binary lifting**. Requires handling lots of cases: all cases in a successor graph: trees, loops, different connected components, ...

## Range Queries
- List Removals: **find the k-th element** in an ordered set at each step
- Salary Queries: **dynamic range sum queries**, with **coordinate compression** (offline queries): requires using vectors for BIT. Otherwise, can use ordered_set (online queries).
- Distinct Values Queries: Find the number of unique values in subarrays given by queries. Needs offline processing. **Offline queries + Fenwick Tree**: enable and disable each value, to reduce the problem to finding the range sum over activated values in a subarray.

## Tree Algorithms
- Tree matching: **simple greedy algorithm** or **dp on trees**. DP version has some additional considerations: can only choose one out of the children to connect to.
- Tree Distances 1: Max distance for every node. Either **DP solving for all roots** or a **greedy algorithm**: the most distant node of every node is one of the nodes of the diameter.
- Tree Distances 2: Sum of distances for every node to every other node. **DP solving for all roots, based on subtree sizes and distance of root**: based on how much the distance changes when moving to a child.
- Subtree queries: **Euler Tour technique**: PURQ for subtree values
- Company queries 1: Simplest **Binary Jumping**: who is x's parent k levels above (requires -1)
- Company queries 2: Simplest **Lowest Common Ancestor**
- Distance queries: Simplest **distance between two nodes in a tree**
- Path Queries: **Euler Tour + sum of values on path from root**: use RUPQ on resulting Euler Tour
- Distinct colors: **Euler Tour + Range Sum Queries for distinct values in a subtree**: similar to Range-Queries/Distinct-Values-Queries

## Mathematics
- Creating strings 2 and Distributing apples: simple **combination** problems
- Candy lottery: +/- simple **expected values** problem
- Divisor analysis: **number theory** to compute the **number of divisors, sum of divisors and product of divisors** modulo M based on the prime factors of a very large number. Basically, go through the formulas and figure out ways to apply MOD. Requires applying **MOD - 1** to the exponent of the product of divisors, and a trick to divide the exponent by two in the perfect square and non-perfect square cases (for perfect squares, use $(\sqrt{n})^{d(n)}$, otherwise divide a term of the exponent).

## String Algorithms
- Finding Periods: **Z-function** is easier to implement, or **Hashing** in $\mathcal{O}(N \log N)$.

## Geometry

## Advanced Techniques
- Meet in the middle: subset sum problem (how many ways to choose a subset of numbers with sum x) with up to $1e9$.
- New Roads Queries: **find maximum along paths from any two pair of nodes** (queries): use **MST** to filter the edges to make a tree since we want to minimize the maximum along any path and use **binary lifting** to get the maximum along the paths.

## Bitwise
- Maximum xor subarray: greedy with **TRIE** to find best previous prefix sum to use for the current index

## Advanced Graph Problems
- Graph Girth: **find shortest cycle length** in undirected unweighted graph - **BFS** for each node

## Counting Problems
- Empty String: **Range DP**, with $\mathcal{O}(N^2)$ state and $\mathcal{O}(N)$ transition. In each state, compare the first character with all of the characters in the interval. Also requires some combinations work for the transition.

## Additional problems 1
### Stacks
- Advertisement: **find nearest smaller element to left and to right** for each position - **Monotonic stack both ways**
### Binary Lifting:
- Cyclic Array: build an **explicit graph** (successor graph) from each array position, then use **binary lifting similarly to LCA (go until $at < dst$)**

## Codeforces

### Strings
- https://codeforces.com/contest/2104/problem/E: method to efficiently test subsequence using a next array
