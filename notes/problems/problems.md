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

## Graph Algorithms
- Counting Rooms: counting **connected components** - **DFS**
- Labyrinth: find **shortest path with unweighted edges** from start to end in a labyrinth and specify the path - **BFS**
- Building Roads: number of **connected components** and which edges to add to modify to only 1 CC - **DFS**
- Message Route: **shortest path with unweighted edges** between two nodes and specify the path - **BFS**
- Monsters: **shortest path with unweighted edges** from start to end in a labyrinth and specify the path. Also, avoid monsters - **BFS** from multiple sources

## Tree Algorithms
- Subtree queries: **Euler Tour technique**: PURQ for subtree values


## Mathematics
- Creating strings 2 and Distributing apples: simple **combination** problems
- Candy lottery: +/- simple **expected values** problem

## Additional Problems

### Sorting and Searching


### Graph Algorithms
- Graph Girth: **find shortest cycle length** in undirected unweighted graph - **BFS** for each node

### Stacks
- Advertisement: **find nearest smaller element to left and to right** for each position - **Monotonic stack both ways**



## Codeforces

### Strings
- https://codeforces.com/contest/2104/problem/E: method to efficiently test subsequence using a next array
