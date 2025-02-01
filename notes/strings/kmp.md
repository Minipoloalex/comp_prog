# KMP string matching/searching
Preprocesses the pattern and not the text, opposite of the suffix array.

## Code
Complexity of $\mathcal{O}(N)$ ($M < N$, $N$ size of text, $M$ size of pattern).
```cpp
// A border of a string is a prefix that is also a suffix of the string but not the whole string.
// KMP[i + 1]: contains the length of the longest border of the prefix of P that ends at i
// Example: "abacababc": kmp = [-1, 0, 0, 1, 0, 1, 2, 3, 2, 0]

// Don't confuse the prefix of the border definition with this prefix.
// Here, the prefix that ends at i takes the role of the whole string in the border definition

// Pattern preprocessed (back jumps): [-1, 0, ...]
vector<int> kmp;

// pattern p
void kmpPreprocess(const string &p) {
    int sz = int(p.size());
    kmp.resize(sz + 1);

    int l = -1, r = 0;
    kmp[0] = -1;
    while (r < sz) {    // l < r
        while (l >= 0 && p[r] != p[l]) l = kmp[l];
        l++; r++;

        // Here, we have l >= 0 and r >= 1
        // Comparison of the i'th character corresponds to
        // the (i + 1)'th position in the array
        kmp[r] = l;
    }
}

// pattern p, text t (must call kmpPreprocess(p) before)
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

### Pattern matching additional option
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

To better understand it, you can write the together string for the example at https://cses.fi/problemset/task/1753/.


### Meaning of KMP array
For the prefix string that ends at position $i$, named $S[0:i]$: the KMP value is the longest suffix of that string coincides with a prefix of the string. And we don't want the full string (obviously).

This can also be called the border: check problem https://cses.fi/problemset/task/1732.

**"A border of a string is a prefix that is also a suffix of the string but not the whole string. For example, the borders of abcababcab are ab and abcab."**

In KMP, we usually want the biggest border for each prefix of the pattern. In this problem, we want all of the borders of the complete string:
```cpp
j = n;  // size
while (kmp[j] > 0) {
    cout << kmp[j] << " ";  // kmp[j] is border size
    j = kmp[j];
}
cout << '\n';
```

This code is easy to understand if we think of the example they gave.


### Preprocessing

Notes about the preprocessing - `kmpPreprocess`:
- The first iteration is always going to be setting the "first" position of the array $kmp[1] = 0$ and going to $l = 0$, $r = 1$.
- On the next iterations, if $l$ ever gets to $-1$, meaning that we have no match whatsoever, we are just going to set $kmp[r] = 0$.
    * If there isn't a match in characters $l$ and $r$, we want to go to the index which is the value in the table of the previous character. Since we are using 1-index, we can just do $l = kmp[l]$: index $l$ references character at index $l - 1$.


Can be confusing:
We want to go to that index because, even though we did not match that character, the previous was previously matched -> might be useful if we can match it (not the biggest match as we wanted, but a smaller thing that may or not match).

To better understand this, trace the code for the string `abacababc`, where `kmp = [-1, 0, 0, 1, 0, 1, 2, 3, 2, 0]`

The values of the KMP array can be interpreted as follows:

### Search

The `kmpSearch` code is very similar to the previous and uses the same ideas.

Additional notes on the code:
- When finding a match, we act as if this was a mismatch on the new character (non-existing in the pattern) and continue looking for more matches. In fact, since we will be at indices incremented by 1 from the last matched character and are using 1-indexed for the $kmp$ array, we can directly reference $kmp[j]$. E.g.:
    - $t = abrabra$ (indexed by $i$)
    - $p = abra$ (indexed by $j$)
    - $kmp = [-1, 0, 0, 0, 1]$
    - $i = 4$, $j = 4$, $j = kmp[4] = 1$, now analyzing $p[1] = $ 'b' and $t[i] = t[4]$

- After finding a match, $i - j$ gives the index with the first character corresponding to the matching. The size of the match is simply $j$ or $m$ (the size of the pattern). E.g.:
    - $t = abrabra$ (indexed by $i$)
    - $p = abra$ (indexed by $j$)
        - When we find the first match, we will have $i = 4$ and $j = 4$. The starting index is $i - j = 0$ and the size of the match is $m = j = 4$.
        - When we find the second match, we will have $i = 7$ and $j = 4$. The starting index is $i - j = 3$.

Note how $i$ corresponds to the index after the final character matched (it is exclusive). If it was inclusive, then we would have to add one: $i - j + 1$. $i - j$ is used because $i$ is exclusive and $j$ is the size.


## Problems
Simplest:
1. https://cses.fi/problemset/submit/1753/
2. https://cses.fi/problemset/task/1732

Harder:
3. https://codeforces.com/contest/432/problem/D: Builds on 2, idea of representing KMP as a tree.
