## Suffix Array
Here, we will focus more on the applications of the suffix array than on how to build it. https://usaco.guide/adv/suffix-array contains a good explanation on each step of the building process and the general reasoning.

### LCP($i$,$j$)
To find $LCP(i, j)$, i.e., the **longest common prefix** of the **suffixes starting at $i$ and $j$**, we can find the minimum $LCP$ value between the positions in the suffix array of the suffixes $i$ and $j$ (using a sparse table or a segment tree).

>---
>The first video from https://codeforces.com/edu/course/2/lesson/2/4 contains a good explanation and a small proof of this.
>
>---

### A good way to think about LCP and why these applications/algorithms work
For example, for the longest repeated substring problem, we want to get for each suffix $i$, the largest LCP with another suffix $j$, since this is the largest possible substring that can start at $i$. WLOG, let's assume the suffix starting at $i$ is smaller than the suffix starting at $j$: we want $j$ to be just after $i$ if $j$ has the largest LCP with $i$.

We can **prove this** by contradiction. There is also a cleaner and more clear proof in the second video from https://codeforces.com/edu/course/2/lesson/2/5.
- Start by saying $j$ is the suffix just after $i$ in the suffix array.
- Let's say there is another prefix $k$ with a larger LCP with $i$ than $j$ does. If it has a larger LCP with $i$, i.e., more common characters with $i$ than $j$ does, then for sure the suffix starting at $k$ is smaller than the suffix starting at $j$, meaning that it will be closer to $i$ in the suffix array (hence $j$ is not after $i$, which gives us the contradiction).

### Proofs
Usually we can do proofs like the two previous ones (from LCP and from LCS/LRS), just as the videos from https://codeforces.com/edu/course/2/lesson/2/4 show (starting at step 4).


### Applications
- **String matching** in $\mathcal{O}(m + \log n)$
- Finding **LRS** in $\mathcal{O}(n)$
- Finding **LCS** (Longest Common Substring) in $\mathcal{O}(N)$
- Other substring related applications

>---
>I believe this is wrong:
"For many of these applications, and to better understand the algorithms, it may be useful to visualize them in a **Suffix Tree** and then convert the algorithm to the Suffix Array and LCP".
>
>---

### Simplest Problems
- Suffix Array construction and `SA` usage: [Kattis - suffixsorting](https://open.kattis.com/problems/suffixsorting)
- Suffix Array `LCP` usage through Longest repeated substring $(LRS)$: [Kattis - repeatedsubstrings](https://open.kattis.com/problems/repeatedsubstrings)

Library checker problems:
1. https://judge.yosupo.jp/problem/suffixarray
2. https://judge.yosupo.jp/problem/number_of_substrings
3. https://judge.yosupo.jp/problem/longest_common_substring

### Common-ish Patterns
Notice how the **LCP($i$,$j$)** between two suffixes starting at $i$ and $j$ is the minimum of the $LCP$ in the middle of their corresponding indices in the suffix array. This means that we can interpret LCP's in a different way and try to think of contributions. This leads to a common pattern of using **monotonic stack** and **next smaller** to find the range in which an LCP contributes. For instance, this corresponds to the range in which the prefix of a specific suffix occurs. When we reach a smaller value, then the LCP with those suffixes will not correspond to that substring, therefore the "contribution" of the LCP ends there.

In fact, for a given LCP value in an index $i$ (this LCP value corresponds to a specific substring, i.e., the prefix of length $lcp[i]$ of suffix starting at $i$), we know that the substring occurs only in between $[\text{prv\_smaller}(i, lcp[i]), \text{nxt\_smaller}(i, lcp[i])]$.

Example problems:
- https://codeforces.com/edu/course/2/lesson/2/5/practice/contest/269656/problem/D: haven't solved but I'm pretty sure it's a similar idea
- https://codeforces.com/edu/course/2/lesson/2/5/practice/contest/269656/problem/E, which just turns into CSES/advertisement: https://cses.fi/problemset/task/1142

### Unique substrings calculation
See library checker problem 2.

A crucial observation to be made for this problem is that every substring can be represented as a prefix of some suffix

#### Number of (non-unique) substrings
A string of size $n$ has $ n + n - 1 + ... + 1$ = $n * (n + 1) / 2$ total substrings.

#### LCP array observation
If the LCP value at a certain index is $X$, then there are $X$ characters in common between the two suffixes. In other words, there are $X$ repeated substrings between those two suffixes, since they come from the same larger string.

The substrings counted from each prefix are only the prefixes (otherwise, there would be overcounting).

Example string: $\texttt{"AZAZA"}$

| LCP | Sorted suffixes | What to do | What substrings we are considering|
|:-:|:-     |:-| :-:|
|0  |A      | + 1 - 0 |   A |
|1  |AZA    | + 3 - 1 | AZA, AZ, <span style="color:yellow">A</span> |
|3  |AZAZA  | + 5 - 3 | AZAZA, AZAZ, <span style="color:yellow">AZA</span>, <span style="color:yellow">AZ</span>, <span style="color:yellow">A</span> |
|0  |ZA     | + 2 - 0 | ZA, Z |
|2  |ZAZA   | + 4 - 2 | ZAZA, ZAZ, <span style="color:yellow">ZA</span>, <span style="color:yellow">Z</span> |

Since we are using suffixes, we will only be considering at each iteration the substrings starting at the index of each suffix, i.e., the prefixes (meaning that we do not consider substrings that do not start at the first character of the suffix).

- $i = 0$, $LCP[i] = 0$, $len(suffix) = 1$, we add $1$
- $i = 1$, $LCP[i] = 1$, $len(suffix) = 3$, we add $3 - LCP[i] = 3 - 1 = 2$
- $i = 2$, $LCP[i] = 3$, $len(suffix) = 5$, we add $5 - LCP[i] = 5 - 3 = 2$
- $i = 3$, $LCP[3] = 0$, $len(suffix) = 2$, we add $2$
- $i = 4$, $LCP[4] = 2$, $len(suffix) = 4$, we add $4 - LCP[i] = 4 - 2 = 2$

In total, $result = 1 + 2 + 2 + 2 + 2 = 9$ or use an [easier formula](#formula).

Basically, we do not count substrings of the current suffix that are common with the previous suffix (considering always substrings that start at the first character of the suffix). We are essentially removing the substrings that come from the common prefixes.

#### Formula
An easier formula to implement:
$$ \frac{n (n + 1)}{2} - \sum_{i = 1}^{n}{LCP[i]}$$



### Longest common substring
Explanation taken from [https://cs.stackexchange.com/questions/9555/computing-the-longest-common-substring-of-two-strings-using-suffix-arrays](https://cs.stackexchange.com/questions/9555/computing-the-longest-common-substring-of-two-strings-using-suffix-arrays):
```
Given two strings A and B, we concatenate them as S=A#B, where # is a character not present in both A and B. The reason for choosing such a character is so that when computing the LCP of two suffixes, say ab#dabd and abd, the comparison will break off at the end of the first string (since it only occurs once, two different suffixes will never have it in the same position), and won't "overflow" into the other string

Now, you should be able to see why you only need to see consecutive values in the LCP array (the argument is based on contradiction and the fact that the suffixes in SA are in lexicographic order). Keep checking the LCP array for the maximum value such that the two suffixes being compared do not belong to the same original string. If they don't belong to the same original string (one begins in A and the other in B), then the largest such value is the length of the largest common substring.
```

Actually, in the implementation, we do `s = a + '#' + b + '$'`


### Code
Find the code [here](../../cp4/ch6/sa_lcp.cpp), adapted from the CP4 book.
