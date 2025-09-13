# Trie

```cpp
int trie[MAX][A];   // A is the size of the alphabet
```
e.g.:

```cpp
int trie[MAX][26];  // A = 26
```

**Usage**: Using a trie, we can find the longest prefix of a given string such that the prefix belongs to a given set. In addition, by storing counts (in a `stop` array), we can calculate the number of strings that belong to the set and have a given string as a prefix.


## Bitwise-Trie
Similar to a normal trie, but with only 2 values (bit values).


```cpp
int trie[MAX][2];   // A = 2
```
