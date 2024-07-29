## Needleman-Wunsch algorithm
### Scoring systems (Basic)

The simplest scoring schemes simply give a value for each match, mismatch and indel. The step-by-step guide above uses match = 1, mismatch = −1, indel = −1. Thus the lower the alignment score the larger the edit distance, for this scoring system one wants a high score. Another scoring system might be:

-    Match = 0
-    Indel = -1
-    Mismatch = -1

For this system the alignment score will represent the edit distance between the two strings. Different scoring systems can be devised for different situations, for example if gaps are considered very bad for your alignment you may use a scoring system that penalises gaps heavily, such as:

-    Match = 1
-    Indel = -10
-    Mismatch = -1


## Longest increasing subsequence (LIS)

Check [LIS](LIS/) directory for notes on the algorithms to solve LIS (in $O(NlogN)$).



## Longest common subsequence (LCS) of 2 permutations (1-n) using LIS

Based on ChatGPT explanation at: https://chatgpt.com/share/c118cf45-38e4-41de-9918-e672821137e1 and on https://codeforces.com/blog/entry/99907.

To convert the problem of finding the Longest Common Subsequence (LCS) of two permutations of length nn into a problem of finding the Longest Increasing Subsequence (LIS), we can leverage the fact that both sequences are permutations of the same set of elements. Here is a step-by-step explanation of how to achieve this conversion:
Step-by-Step Process:

Using this example:

$$P=[3,1,2,4] , Q=[1,4,2,3]$$


1. Label the elements: Given two permutations $P$ and $Q$ of length $n$, we first create a mapping from the elements of $Q$ to their positions.
```
# Indices are elements of the permutation, values are their indices in Q
pos = [0] * n

for i in range(n):
    pos[Q[i] - 1] = i   # (Q[i] ∈ [1, n])
```
$$Q_{mapping}=\{1→0,4→1,2→2,3→3\}$$


2. Create the mapped sequence: Replace each element in $P$ with its corresponding position in $Q$. This transformation results in a new sequence $R$.

$$P→R=[3,0,2,1]$$

3. Find LIS of the mapped sequence: the Longest Increasing Subsequence (LIS) of this new sequence $R$ will be equivalent to the Longest Common Subsequence (LCS) of the original sequences $P$ and $Q$.


The LIS of RR is:

$$LIS(R) = [0,2]$$

The length of this LIS is 2. Thus, the length of the LCS of $P$ and $Q$ is also 2.

Check https://codeforces.com/gym/104349/problem/D and [codeforces/gym/104349/problemD/problemD.cpp](../../codeforces/gym/104349/problemD/problemD.cpp)

