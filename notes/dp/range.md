## Range DP

Typically $N = 500$, and solution is $\mathcal{O}(N^3)$. The $DP$ array is based on subarray intervals: $DP[i][j]$, with the transition being commonly $\mathcal{O}(N)$.

A **common pattern** is trying to match the first value/character (possibly) with each value/character inside the interval $[i,j]$ from the $DP$ state. Then, handling the interval in the middle $[i+1,idx-1]$ and the interval after $[idx+1,j]$. See example problems.

### Example problems:
- https://saco-evaluator.org.za/cms/sapo2015z/tasks/jazz/description
- https://codeforces.com/problemset/problem/607/B
- https://codeforces.com/contest/1776/problem/B
