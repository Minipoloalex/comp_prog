## Tips
A variable probably should not be at the same in the state of a DP and in the transition with a for loop.
It is likely that we can remove the variable from the state and compute the result for all possible variable values in the for loop.

An example problem, where this reduces the complexity from $\mathcal{O}(n\log^2{n})$ to $\mathcal{O}(n\log{n})$: https://codeforces.com/problemset/problem/1988/D
