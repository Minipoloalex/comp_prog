## String matching
**Pattern matching problem**: Given string $s$ and pattern $p$, find positions where $p$ occurs in $s$: $\mathcal{O}(N)$.

This can be done in several ways:
- Using C++ `find`: $\mathcal{O}(N^2)$
- Going through $s$ with a sliding window and checking **hashes** comparison to $p$.
- Using **KMP**: preprocesses the pattern P. Calculates longest border for every prefix of P: see [kmp.md](kmp.md)
- Using **Z-algorithm**: concatenating text and pattern with delimiter: see [z-algorithm.md](z-algorithm.md)
- Using **Suffix Array**

