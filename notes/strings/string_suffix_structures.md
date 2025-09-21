# Suffix Trie, Suffix Tree and Suffix Automaton
Based on CP4 book, by Steven Halim.

## Suffix Trie
A suffix trie of a set of strings is a tree of all possible suffixes of strings in S.
- Each vertex can be connected up to $|\Sigma|$ number of vertices (size of alphabet).
- The common prefix of two suffixes is shared
- Each vertex has 2 boolean flags: exists a suffix or word that terminates in that node.

For example:


`Dictionary = {‘CAR’, ‘CAT’, ‘RAT’}`

After sorting and removing duplicates, we have:

`Suffixes = {‘AR’, ‘AT’, ‘CAR’, ‘CAT’, ‘R’, ‘RAT’, ‘T’}`

![alt text](images/image.png)

### Applications
Suffix Trie is typically used for a dictionary. Assuming it has been built for a set of strings, determining if a pattern P exists in the dictionary (Suffix Trie) can be done in $\mathcal{O}(m)$.

A bBST may also work for this use case. The complexity with a bBST is $\mathcal{O}(m * \log N)$, as each comparison costs $\mathcal{O}(m)$.

## Suffix Tree
Suffix Tree of a string is a Suffix Trie where vertices with only one child are merged (path compression). Much more compact with at most $\mathcal{O}(N)$ vertices (and edges).


`$` is assumed to be smaller than any character of the string.

**Suffix Trie** on the middle, **Suffix Tree** on the right:

![alt text](images/image-1.png)

### Applications
Suffix Tree preprocesses the string, not the patterns.

Assuming it is built on a string T, we can perform:
- **string matching** in $\mathcal{O}(m + occ)$, where `m = pattern.size()` and `occ` is the number of occurrences of the pattern in T.
    - Traverse the Suffix Tree until matching the complete pattern. The size of the subtree found respects: `subtree_size <= 2 * occ`.
- **longest repeated substring** in $\mathcal{O}(N)$: longest substring that occurs at least twice.
    - Find the deepest internal vertex (not leaf) using a DFS/BFS.
- **longest common substring** in $\mathcal{O}(N)$: for 2 or more strings.
    - Build a suffix tree with all strings
    - Find the deepest internal vertex that contains children of every string (it a prefix that is shared by suffixes of every string)
    - Consider every string needs to be marked differently at its end (for instance, `s = "steven$"`, `t = "seven#"`, `u = "eve@"`).


## Suffix Automaton
?
