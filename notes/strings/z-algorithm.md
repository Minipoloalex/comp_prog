# Z Algorithm
Based on https://usaco.guide/adv/string-search?lang=cpp.

Similar, but uses a different function in comparison to KMP.

It uses the **Z-function**:

**Given a position, this function gives the length of the longest string that's both the prefix of  $S$ and of the suffix of  $S$ starting at the given position**.

Basically, at position $i$, it gives the length of the prefix of the string that's the same as the prefix of the suffix that starts at $i$. For instance, the first value is always the size of the string.

$$ Z[i] = max_r(S[0:r] = S[i:i+r])$$
where:
- $r$ is the length of that prefix
- $S[0:r]$ represents the prefix of length $r$ of the string $S$
- $S[i: i + r]$ represents the prefix of length $r$ of the suffix that starts at $i$ of the string $S$

Note this $r$ is not related to the $r$ in the code below.

## Examples

For $S = \texttt{"aabxaayaab"}$:
$$Z=[10, 1, 0, 0, 2, 1, 0, 3, 1, 0]$$

For $S = \texttt{"aabxaabxcaabxaabxay"}$:
$$Z = [19, 1, 0, 0, 4, 1, 0, 0, 0, 8, 1, 0, 0, 5, 1, 0, 0, 1, 0]$$


## Code

```cpp
vector<int> z_function(const string &s) {
	vector<int> z(s.size());
	z[0] = s.size();

	int l = 0, r = 0;
	for (int i = 1; i < s.size(); i++) {
		z[i] = max(0, min(z[i - l], r - i + 1));
		while (i + z[i] < s.size() && s[z[i]] == s[i + z[i]]) {
			l = i;
			r = i + z[i];
			z[i]++;
		}
	}

	return z;
}
```
