## String matching
**Pattern matching problem**: Given string $s$ and pattern $p$, find positions where $p$ occurs in $s$: $\mathcal{O}(N)$.

This can be done in several ways:
- Using C++ `find`: $\mathcal{O}(N^2)$
- Going through $s$ with a sliding window and checking **hashes** comparison to $p$.
- Using **KMP**: preprocesses the pattern P. Calculates longest border for every prefix of P: see [kmp.md](kmp.md)
- Using **Z-algorithm**: concatenating text and pattern with delimiter: see [z-algorithm.md](z-algorithm.md)
- Using **Suffix Array**

| Approach         | Best For                                      | Complexity | Notes |
|-----------------|---------------------------------|------------|-------------|
| **Suffix Array**  | Many substring queries, LCP, lexicographic order | $\mathcal{O}(n \log n)$ for construction, $\mathcal{O}(m + \log n)$ for search | Best for multiple queries |
| **KMP**          | Single pattern search in a long text  | $\mathcal{O}(n + m)$ | Preprocesses pattern, fast search |
| **Rabin-Karp**   | Multiple pattern search, rolling hash checks | $\mathcal{O}(n + m)$ (avg) | Hashing makes it fast, beware of collisions |
| **Standard Libs** | Small constraints, quick implementation | $\mathcal{O}(nm)$ worst | Easy, but not always optimal |

If a problem involves many substring queries, go for Suffix Arrays. If you only need one occurrence search, go for KMP. If hashing helps (e.g., checking equality of substrings quickly), Rabin-Karp is useful. And if constraints are small, just use built-in functions.

## Useful constructions
Generally, the delimiters used cannot be part of the strings.

### KMP
#### Pattern Matching
$$ s = p + \texttt{"\#"} + t $$

```cpp
string together = p + '#' + t;
kmpPreprocess(together);

for (int i = 0; i < int(kmp.size()); i++) {
    if (kmp[i] == int(p.size())) {
        cout << "Match found at index " << i - int(p.size()) << " of together\n";
        cout << "Match found at index " << i - 2 * int(p.size()) - 1 << " of text\n";
        // -1 accounts for the delimiter
        // kmp[i + 1] -> corresponds to index i of the string
        // i - p.size() -> gives starting index of match (i corresponds to S[i - 1])
    }
}
```

#### Longest Prefix (or Suffix) Palindrome
```cpp
// Pseudo-code:

string rev = reverse(s);

kmpPreprocess(s + '#' + rev);
s.substr(0, kmp.back())     // longest prefix palindrome

kmpPreprocess(rev + '#' + s);
rev.substr(0, kmp.back());  // longest suffix palindrome
```

### Z-algorithm
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

### Suffix Array
Always assumes the delimiter characters don't appear in the strings, and that they are smaller than any character that appears in the strings. You can use `'\1'`, `'\2'`, ...
#### Longest Common Substring
```cpp
string s = a + '#' + b + '$';
```
