# CSES
## Introductory
- Apple Division: classic **Minimum Subset Sum Difference** NP-hard problem. Brute force $\mathcal{O}(2^N)$


## Sorting and Searching
- Nearest Smaller Values: for each index, find nearest position to left having a smaller value - **Classic monotonic stack**
- Playlist: **two pointers** with set
- Missing coin sum: simple **greedy with sorting**
- Collecting Numbers: **simulate efficiently** by making an array with the positions of each permutation value.
- Dinstinct Values Subarray: count the number of subarrays with distinct values. Can be seen as a **classic subarrays problem**: here, we count how many valid subarrays end at position $i$. We can use **two pointers** to maintain the current valid maximum size subarray. Basically we maintain a **sliding window** on distinct values, with a map.
- Distinct Values Subsequences: count the number of subsequences with distinct values: from a specific value, we can choose to take any of its indices or none. We just need to remove the empty case.
- Reading Books: greedy based on a cool construction: sort by non-decreasing (check editorial)
- Maximum subarray sum 2: **sliding window on prefix sums** to find valid minimum for max subarray sum
- Subarray Sums 1:
    * We can do the usual prefixes with a map, but we can also use two-pointers (editorial), since all sums are positive
- Subarray Sums 2:
    * Here, we'll need to do the prefixes with a map (we can use the exact same code) as in 1.
- Subarray Divisibility:
    * Similar idea to above, but here, we will bucket the values directly into a vector to count them (because we're doing MOD).

## Dynamic Programming
- Longest Common Subsequence: classic LCS, requires reconstruction
- Rectangle Cutting: simple/obvious Range DP. Required iterative DP to avoid TLE (but still very simple/intuitive to code).
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
- High Score: **Bellman-Ford (negative cycle application)**
- Flight Discount: example of **adapting Dijkstra with flags**: distance array with >1D. Another possible solution is more ad-hoc (solution 1 from https://usaco.guide/problems/cses-1195-flight-discount/solution)
- Cycle Finding: **Bellman-Ford to detect any negative cycle**: requires adapting Bellman-Ford to detect negative cycles regardless of shortest paths (not just those reachable from node $0$).
- Round trip 2: find any cycle in a directed graph
- Course Schedule: simplest **topological sort**
- Longest Flight Route: simple **DP in a DAG**: find longest path in a DAG
- Game Routes: simple **DP in a DAG**: find number of ways to go from $a$ to $b$
- Road Reparation: simplest **MST**: using Kruskal or Prim
- Road Construction: classic **DSU to get connected components** number and max size.
- Planets queries 1: go through k nodes in a **successor graph**: simple **binary lifting**
- Planets queries 2: determine minimum number of jumps to get from node $a$ to $b$ in a **successor graph**: **binary lifting**. Requires handling lots of cases: all cases in a successor graph: trees, loops, different connected components, ...
- Planets and Kindgoms: simplest **Strongly Connected Components**
- Coin Collector: simplest **DP on SCCs DAG**
- Giant Pizza: **simplest 2-sat problem**

## Range Queries
- Static Range Minimum Queries:
    - Simply use a **Segment Tree** or a **Sparse Table**
    - Use a **divide and conquer** approach to answer **offline queries** about associative operations.
    - Use a **divide and conquer** approach to save a 2D array using only $\mathcal{O}(N \cdot \log{N})$ memory, similar to a Sparse Table, then **answer queries online** (not implemented).
- Dynamic Range Sum Queries:
    - BIT or Segment Tree
    - Square Root Decomposition style, using **blocking**.
- Range XOR Queries: **static prefix XOR sums**
- Hotel Queries: **walking on a Segment Tree**: segment tree to keep maximums and corresponding ids (for same maximums, keep first id).
- List Removals: **find the k-th element** in an ordered set at each step
- Salary Queries: **dynamic range sum queries**, with **coordinate compression** (offline queries): requires using vectors for BIT. Otherwise, can use ordered_set (online queries).
- Prefix Sum Queries:
    - Use a **Segment Tree** to keep track of the maximum prefix sum and the total sum: $pref = max(pref_1, sum_1 + pref_2)$ and $sum = sum_1 + sum_2$.
    - More complicated/elaborate, but good as a thinking exercise: Use a **Lazy Propagation Segment Tree** that **stores the actual prefix sums array and does maximum**. Then, each query to update a single position $k$ should update the range $[k, n-1]$ (add to that range) with $AddValue = a[k]_{new} - a[k]_{old}$. To answer queries, we want the maximum prefix sum in $[a,b]$, so we can get the maximum prefix sum in that range, and then subtract the exact prefix sum $pref[0, a-1] = range\_query(a-1,a-1)$.

- Pizzeria Queries: Answer queries (and do point updates) answering which pizza is cheaper for a building, with each building have a pizzeria costing $p_k$ and the cost of travelling from $a$ to $b$ being $|a - b|$. Use a **Segment Tree** that **keeps track of the best result to the left and the best result to the right**. My implementation kept the indices and computed the costs for the left and right, computing the comparison costs each time. The CSES implementation uses only two values instead.
    * Instead, we can do a more elegant solution. You can start from writing the minimum on paper, then splitting it for the right and left to get rid of the absolute value. Then, we can just maintain two segment trees, one for querying the left and another one for querying the right.
- Range Interval Queries: several possible solutions
    - online with 2D Fenwick Tree: TLEs
    - online with Persistent Segment Tree: barely passes
    - Merge-sort like (Editorial): keep an array with the segment tree node's values
    - Offline processing by sweeping based on events, using a segment tree (Editorial): process queries in order of one dimension, keep a segment tree on the normal array indices
- Forest Queries 2: simplest **2D Fenwick Tree (Online)**
- Range Updates and Sums: **range adds**, **range sets** and **range sums**: use a **Lazy Segment Tree**, with multiple `LazyUpdate` types.

- Subarray Sum Queries (and Subarray Sum Queries 2): Find the **subarray with the maximum sum on an interval**. Use a **Segment Tree** that keeps track of **prefix** subarray maximum sum, **suffix** subarray maximum sum, **maximum** sum, and total **sum**. We can use these auxiliar values to compute the maximum subarray sum.
- Distinct Values Queries: Find the number of unique values in subarrays given by queries. Needs offline processing. **Offline queries + Fenwick Tree**: enable and disable each value, to reduce the problem to finding the range sum over activated values in a subarray. The idea is to "activate" each value the closest to the current index $i$ (the closest to the right, which is the best possible for intervals that end at $i$, and span across to the left).

- Range Queries and Copies: simplest **Persistent Segment Tree** problem

## Tree Algorithms
- Tree matching: **simple greedy algorithm** or **dp on trees**. DP version has some additional considerations: can only choose one out of the children to connect to.
- Tree Distances 1: Max distance for every node. Either **DP solving for all roots** or a **greedy algorithm**: the most distant node of every node is one of the nodes of the diameter.
- Tree Distances 2: Sum of distances for every node to every other node. **DP solving for all roots, based on subtree sizes and distance of root**: based on how much the distance changes when moving to a child.
- Subtree queries: **Euler Tour technique**: PURQ for subtree values
- Company queries 1: Simplest **Binary Jumping**: who is x's parent k levels above (requires -1)
- Company queries 2: Simplest **Lowest Common Ancestor**
- Distance queries: Simplest **distance between two nodes in a tree**
- Path Queries: **Euler Tour + sum of values on path from root**: use RUPQ on resulting Euler Tour
- Path Queries 2: Classic **Heavy-Light Decomposition**: find max along a path and update nodes. Lazy segment tree may TLE, so just adapt HLD to the point update version (iterative).
- Distinct colors: **Euler Tour + Range Sum Queries for distinct values in a subtree**: similar to Range-Queries/Distinct-Values-Queries

## Mathematics
- Creating strings 2 and Distributing apples: simple **combination** problems
- Divisor analysis: **number theory** to compute the **number of divisors, sum of divisors and product of divisors** modulo M based on the prime factors of a very large number. Basically, go through the formulas and figure out ways to apply MOD. Requires applying **MOD - 1** to the exponent of the product of divisors, and a trick to divide the exponent by two in the perfect square and non-perfect square cases (for perfect squares, use $(\sqrt{n})^{d(n)}$, otherwise divide a term of the exponent).
- Counting Coprime Pairs: In an array, count the number of pairs that are coprime.
    * **PIE** approach in $\mathcal{O}(n\cdot (\sqrt{MAX} + 2^K \cdot K)) = 1e8$. Basically, for each number, we want to exclude all other numbers that share a prime. We can get the size of sets like $P_1 \cap P_2 \cap \dots \cap P_k$ by first precomputing, for all divisors, how many numbers in the array are divided by them. Another possible solution would be to update the counts of how many numbers each prime divides as we go through all subsets of primes of a specific number: Check https://cses.fi/problemset/model/2417/.
- Next Prime: based on the size of **prime gaps**, which are relatively small. Using a prime check in $\mathcal{O}(\frac{\sqrt{N}}{\log_2{\sqrt{N}}})$ easily passes. We can even use something slower (editorial does a simple $\mathcal{O}(\frac{\sqrt{N}}{2})$ prime check). Check math notes and wikipedia about prime gaps.
- Christmas Party: just asks $!n$, i.e., the derangements.
- Fibonacci Numbers: simplest **matrix exponentiation** problem (code in [Errichto Gym Problem C](../../codeforces/gym/102644_matrix_exponentiation/C/C.cpp))
- Graph Paths 1: **matrix exponentiation** problem for counting paths of exactly $k$ edges between two nodes.
- Graph Paths 2: **matrix exponentation** problem for determining minimum path of exactly $k$ edges. Requires adapting matrix multiplication (here we should call it combining matrices, since it's not multiplication). To do matrix exponentiation, we should be careful when setting the identity matrix.
    * An interesting way to think about this problem is to try and combine two paths to make a larger one (see matrix exponentiation notes).
- Candy lottery: +/- simple **expected values** problem

## String Algorithms
- Finding Periods: **Z-function** is easier to implement, or **Hashing** in $\mathcal{O}(N \log N)$.
- String Functions: **Z-function** and **prefix function** templates

## Geometry
- Intersection points: **intersections between horizontal and vertical lines**: use sweep line. Build an events list, and go through $x$ (for example), with horizontal segments being added to a **Fenwick Tree** for querying on vertical segments (query range $[y_1, y_2]$). After an horizontal segment ends, we remove it from the Fenwick Tree.
- Area of the union of rectangles: **sweep line algorithm** with a data structure (e.g. **count minimums in a segment tree**).
- All Manhattan Distances: simple Manhattan distances observation: $X$ and $Y$ coordinates are completely independent here. We can just sort the coordinates and sum based on prefixes. It can help to explicitly write the formula down and simplify/optimize it.
    * This problem looks like it can overflow from 64 bits, so I solved it in Python, which worked.

## Advanced Techniques
- Meet in the middle: subset sum problem (how many ways to choose a subset of numbers with sum x) with up to $1e9$.
- Hamming Distance: use **bitwise optimizations**. Basically, we can make every value an integer (read it using a bitset, for instance) and compare numbers by counting the number of bits (popcount) of the XOR.
- Corner Subgrid Count: use bitsets. Using STL bitset TLEs unless you use pragmas.
- Reachable Nodes: use bitsets and do simple bitwise-or based on a topological sort. Don't necessarily need pragmas even with STL bitsets (note that constant factor is divided by 32).
- New Roads Queries: **find maximum along paths from any two pair of nodes** (queries): use **MST** to filter the edges to make a tree since we want to minimize the maximum along any path and use **binary lifting** to get the maximum along the paths.
- Monster Game: classic convex hull trick
    * Monster Game I: convex hull trick with monotonic slopes and queries (decreasing slopes, increasing queries)
    * Monster Game II: convex hull trick with no special properties: use a LineContainer or a LiChaoTree
- Subarray Squares:
    * **Convex Hull Trick** Solution. Need to be careful to reset hull when going to the next level, and also to ensure start from valid "position".
    * **Divide & Conquer** Solution: TODO (study topic)

- Parcel Delivery: simplest **Minimum Cost Max Flow** problem, with all costs being positive.
- Task Assignment: simplest **Minimum Cost Bipartite Matching** with **Hungarian Algorithm** (with $n = m$). Requires outputting assignments.

## Bitwise
- Maximum xor subarray: greedy with **TRIE** to find best previous prefix sum to use for the current index

## Advanced Graph Problems
- Graph Girth: **find shortest cycle length** in undirected unweighted graph - **BFS** for each node

## Counting Problems
- Empty String: **Range DP**, with $\mathcal{O}(N^2)$ state and $\mathcal{O}(N)$ transition. In each state, compare the first character with all of the characters in the interval. Also requires some combinations work for the transition.

## Additional problems 1
### Stacks
- Advertisement:
    * **find nearest smaller element to left and to right** for each position - **Monotonic stack both ways**
    * Another solution involves only one pass, by saving pairs: $(\text{start}, \text{height}[i])$ in an increasing monotonic stack. $\text{start}$ corresponds to the leftmost possible start for the $i$'th fence. Check https://usaco.guide/problems/cses-1142-advertisement/solution#solution-2. We account for the right "propagation" of a specific fence $i$ by only taking the answer for that fence after finding a smaller fence $j$ (which is after $i$).
- Maximum Building 1: stack-based approach, the same as advertisement (e.g. for each column), after a preprocessing step.
    * The preprocessing is making the grid have in each position the longest consecutive number of trees to its right.
    * Afterwards, we can just use a maximum area algorithm (CSES/advertisement) for each column independently.

### Binary Lifting:
- Cyclic Array: build an **explicit graph** (successor graph) from each array position, then use **binary lifting similarly to LCA (go until $at < dst$)**

## Additional problems 2
- School Excursion: basically a coins DP problem, but use bitset to pass with $\mathcal{O}(N^2)$ complexity.

## Codeforces

### Strings
- https://codeforces.com/contest/2104/problem/E: method to efficiently test subsequence using a next array
