# Z Algorithm
Based on https://usaco.guide/adv/string-search?lang=cpp.

Similar, but uses a different function in comparison to KMP.

It uses the **Z-function**:

**Given a position, this function gives the length of the longest string that's both the prefix of $S$ and the prefix of the suffix of $S$ starting at the given position**. Check examples below (and maybe a more clear definition as well?).

Check another way to interpret the array: [Library Checker Problem](#library-checker-problem)

Basically, at position $i$, it gives the length of the prefix of the string that's the same as the prefix of the suffix that starts at $i$. For instance, the first value is always the size of the string (it can be seen as undefined, actually).

$$
Z_i = \max\{\, k \mid S_{0..k-1} = S_{i..i+k-1} \,\}.
$$

where:
- $k$ is the length of that prefix
- $S[0:k]$ represents the prefix of length $k$ of the string $S$
- $S[i: i + k]$ represents the prefix of length $k$ of the suffix that starts at $i$ of the string $S$

Basically what's here: https://usaco.guide/problems/cses-1753-string-matching/solution#solution---z-algorithm

## Examples

For $S = \texttt{"aabxaayaab"}$:
$$Z=[10, 1, 0, 0, 2, 1, 0, 3, 1, 0]$$

For $S = \texttt{"aabxaabxcaabxaabxay"}$:
$$Z = [19, 1, 0, 0, 4, 1, 0, 0, 0, 8, 1, 0, 0, 5, 1, 0, 0, 1, 0]$$


## Library Checker Problem
https://judge.yosupo.jp/problem/zalgorithm

Given string $S$ of length $N$: calculate array $a_0,a_1,...,a_{N−1}$ as follows:

$a_i​$ is the **LCP (longest common prefix)** of $S$ and $S.substr(i)$.

where:
- $S.substr(i) \Longleftrightarrow S[i:]$ represents the suffix of string $S$ that starts at position $i$: 

## Code

```cpp
// z[i] is the LCP (longest common prefix) of s and s.substr(i) (suffix of S starting at i: s[i:]).
// For S = "aabxaayaab", Z = [10, 1, 0, 0, 2, 1, 0, 3, 1, 0] (same size as S)
vector<int> z_function(const string &s) {
	vector<int> z(s.size());
	z[0] = (int) s.size();

	int l = 0, r = 0;
	for (int i = 1; i < (int) s.size(); i++) {
		z[i] = max(0, min(z[i - l], r - i + 1));
		while (i + z[i] < (int) s.size() && s[z[i]] == s[i + z[i]]) {
			l = i;
			r = i + z[i];
			z[i]++;
		}
	}
	return z;
}
```

## Pattern matching code
The delimiter must not appear in the strings. Here, we used `#`.
```cpp
string together = p + '#' + t;	// pattern p, text t, delimiter '#'
vector<int> z = z_function(together);
for (int i = 0; i < int(z.size()); i++) {
	if (z[i] == int(p.size())) {
		cout << "Match found at index " << i << " of together\n";
		cout << "Match found at index " << i - int(p.size()) - 1 << " of text\n";
		// -1 accounts for the delimiter
	}
}
```

To better understand it, you can write the together string for the example at https://cses.fi/problemset/task/1753/.


## Problems
Very similar applications to the prefix function (KMP).

Simple:
- Finding periods: https://cses.fi/problemset/task/1733
- Finding borders: https://cses.fi/problemset/task/1732

Basically the same as KMP:
- https://cp-algorithms.com/string/z-function.html#number-of-distinct-substrings-in-a-string
