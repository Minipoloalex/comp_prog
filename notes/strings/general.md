## String matching
**Pattern matching problem**: Given string $s$ and pattern $p$, find positions where $p$ occurs in $s$: $\mathcal{O}(N)$.

This can be done in several ways:
- Using C++ `find`: $\mathcal{O}(N^2)$
- Going through $s$ with a sliding window and checking **hashes** comparison to $p$.
- Using **KMP**: preprocesses the pattern P. Calculates longest border for every prefix of P: see [kmp.md](kmp.md)
- Using **Z-algorithm**: concatenating text and pattern with delimiter: see [z-algorithm.md](z-algorithm.md)
- Using **Suffix Array**

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
