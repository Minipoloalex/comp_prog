## LIS of 2 sequences (Longest non-decreasing subsequence)
We want the LIS (more specifically, the **Longest non-decreasing subsequence**) of the **AND** of 2 sequences. This means that we need to select some indices, such that they're increasing in regards to both a sequence $A$ and a sequence $B$.

For this **Longest non-decreasing subsequence** problem, we can:
- Sort one of the arrays: e.g. $A$
- Perform usual LIS on the second array $B$, sorted according to $A$ (but use `upper_bound` for "LIS" instead to allow the same values to propagate forwards).

## LIS of 2 sequences (strict)
Note that to make it a strict increasing subsequence, we would have to do something different in the sorting step, since here we allow indices with the same value in $A$.
- Sort by increasing values in $A$, and for the same values in $A$, we need to sort in descending order. Basically, as a tie break, we use descending $B$ order. 

This ensures that, for a specific value in $A$, only one is chosen when determining the LIS in $B$.
