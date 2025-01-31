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


## Suffix Array
- Suffix Array construction and `SA` usage: [Kattis - suffixsorting](https://open.kattis.com/problems/suffixsorting)
- Suffix Array `LCP` usage through Longest repeated substring $(LSR)$: [Kattis - repeatedsubstrings](https://open.kattis.com/problems/repeatedsubstrings)

### Unique substrings calculation

#### Number of (non-unique) substrings
A string of size $n$ has $n * (n + 1) / 2$ total substrings.

Substrings that start with index $i$ have size:
- $i = 0: n$
- $i = 1: n - 1$
- $...$
- $i = n - 1: 1$

Arithmetic progression of $n$ elements, first is $n$, last is $1$.
$$ (n + 1) * n / 2 $$

#### LCP array observation
If the LCP value at a certain index is $X$, then there are $X$ characters in common between the two suffixes. In other words, there are $X$ repeated substrings between those two suffixes, since they come from the same larger string.

Example string: $'AZAZA'$

| LCP | Sorted suffixes | What to do | What substrings we are considering|
|:-:|:-     |:-| :-:|
|0  |A      | + 1 - 0 |   A |
|1  |AZA    | + 3 - 1 | AZA, AZ, <span style="color:yellow">A</span> |
|3  |AZAZA  | + 5 - 3 | AZAZA, AZAZ, <span style="color:yellow">AZA</span>, <span style="color:yellow">AZ</span>, <span style="color:yellow">A</span> |
|0  |ZA     | + 2 - 0 | ZA, Z |
|2  |ZAZA   | + 4 - 2 | ZAZA, ZAZ, <span style="color:yellow">ZA</span>, <span style="color:yellow">Z</span> |

Since we are using suffixes, we will only be considering at each iteration the substrings starting at the index of each suffix (i.e. we do not consider substrings that do not start at the first character of the suffix).

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
## Knuth-Morris-Pratt String Matching
Preprocesses the pattern and not the text, opposite of the suffix array.

### Preprocessing

```cpp
vector<int> kmp;

void kmpPreprocess(const string &p) {
    int sz = int(p.size());
    kmp.resize(sz + 1);

    int l = -1, r = 0;
    kmp[0] = -1;
    while (r < sz) {    // l < r
        while (l >= 0 && p[r] != p[l]) l = kmp[l];
        l++; r++;

        // Here, we have l >= 0 and r >= 1
        // Comparison of the i'th character corresponds to the (i + 1)'th position in the array)
        kmp[r] = l;
    }
}
```
Notes about the code:
- The first iteration is always going to be setting the "first" position of the array $kmp[1] = 0$ and going to $l = 0$, $r = 1$.
- On the next iterations, if $l$ ever gets to $-1$, meaning that we have no match whatsoever, we are just going to set $kmp[r] = 0$.
    * If there isn't a match in characters $l/r$, we want to go to the index corresponding to the value in the table of the previous character. Since we are using 1-index, we can just do $l = kmp[l]$: index $l$ references character at index $l - 1$.
<!--
We want to go to that index because, even though we did not match that character, the previous was previously matched -> might be useful
-->

```cpp
void kmpSearch(const string &p, const string &t) {
    int n = int(t.size());
    int m = int(p.size());
    int i = 0, j = 0;   // i loops through text, j through pattern
    while (i < n) {
        while (j >= 0 && (t[i] != p[j])) j = kmp[j];
        i++; j++;
        if (j == m) {
            cout << "Match found starting at index " << i - j << '\n';
            j = kmp[j];  // continue looking for more matches 
        }
    }
}
```
This code is very similar to the previous and uses the same ideas.

Additional notes on the code:
- When finding a match, we act as if this was a mismatch on the new character (non-existing in the pattern) and continue looking for more matches. In fact, since we will be at indices incremented by 1 from the last matched character and are using 1-indexed for the $kmp$ array, we can directly reference $kmp[j]$. E.g.:
    - $t = abrabra$ (indexed by $i$)
    - $p = abra$ (indexed by $j$)
    - $kmp = [-1, 0, 0, 0, 1]$
    - $i = 4$, $j = 4$, $j = kmp[4] = 1$, now analyzing $p[1] = $ 'b' and $t[i]$

- After finding a match, $i - j$ gives the index with the first character corresponding to the matching. The size of the match is simply $j$ or $m$ (the size of the pattern). E.g.:
    - $t = abrabra$ (indexed by $i$)
    - $p = abra$ (indexed by $j$)
        - When we find the first match, we will have $i = 4$ and $j = 4$. The starting index is $i - j = 0$ and the size of the match is $m = j = 4$.
        - When we find the second match, we will have $i = 7$ and $j = 4$. The starting index is $i - j = 3$.


#### Bad implementations
The implementation shown above is very compact and handles edge cases well.

An implementation like the one below can have many bugs. In fact, this implementation has bugs, at least the preprocessing part.
Don't try to understand this, just check how many ifs something badly implemented can have.

```cpp
// There's a bug(s) in this function
void kmpPreprocess(const string &p) {
    int sz = int(p.size());
    kmp.assign(sz, 0);

    int i = 0, j = 1;
    int value = 0;
    while (j < sz) {
        char a = p[i], b = p[j];
        if (a != b && i == 0) {
            kmp[j] = value;
            j++;
        }
        else if (a != b) {
            assert(i > 0);
            i = kmp[i - 1];
            value = kmp[i - 1];
        }
        else if (a == b) {
            value++;
            kmp[j] = value;
            i++; j++;
        }
    }
}

// Untested function
void kmpSearch(const string &p, const string &t) {
    int n = int(t.size());
    int m = int(p.size());
    int i = 0, j = 0;   // i loops through text, j through pattern
    while (i < n) {
        char a = t[i], b = p[j];
        if (a == b) {
            i++; j++;
        }
        else if (a != b && j == 0) {
            i++;
        }
        else if (a != b) {
            assert(j > 0);
            j = kmp[j - 1];
        }
        if (j == m) {
            cout << "Match found starting at index " << i - j << '\n';
            j = kmp[j - 1]; // continue looking for more matches
        }
    }
}
```


