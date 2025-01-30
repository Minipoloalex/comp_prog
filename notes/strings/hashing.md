## CPH
https://usaco.guide/CPH.pdf#page=255

### Setup

- Hash array: $h[k]$ contains hash value of prefix $s[0..k]$
- Power array: $p[k]$ contains the power to $A^k mod B$

To compute the hash of an arbitrary substring $[a, b]$ (if $a \neq 0$):

$$(h[b] - h[a - 1]*p[b - a + 1]) mod B$$
where $b - a + 1$ just represents the size of the substring.

### Uses
- **Pattern matching problem**: Given string $s$ and pattern $p$, find positions where $p$ occurs in $s$: $\mathcal{O}(N)$.
- **$Log(N)$ lexicographic comparison of strings**: we can binary search for the common prefix and compare the next character. (T T ... T F ... F F F: last true binary search for common $h[k]$ hashing value of prefix).

### Collisions
Check the table on the CPH link.


- We can just do more hashes Two hash values with parameter $B \approx 1e9$ correspond to one hash value of $B \approx 1e18$.

Do not use constants $2^{32}$ or $2^{64}$, since specific inputs are known to lead to collisions.



#### Code
Template code to choose a modulo value and a multiplication value:
```cpp
typedef uint64_t hash_t;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
// mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

const int HASH_COUNT = 2;

// this is the prime, the modulo term (aka M)
const hash_t HASH_P = (uint32_t) -13337; // 4294953959
// const hash_t M = HASH_P;

uniform_int_distribution<hash_t> MULT_DIST(int64_t(0.25 * HASH_P), int64_t(0.75 * HASH_P));

// This is the multiplied term (aka B)
const hash_t HASH_MULT[HASH_COUNT] = {MULT_DIST(rng), MULT_DIST(rng)};
// const hash_t *B = HASH_MULT;

// pow[i] contains B^i % M
vector<hash_t> hash_pow[HASH_COUNT];

// p_hash[i] is the hash of the first i characters of the given string
// Prefix [l, r], with sz = r - l + 1
// sl * B^sz-1 + sl + 1 * B^sz-2 + ... + sr * B^0
vector<hash_t> p_hash[HASH_COUNT];

void prepare_hashes(const string &s) {
    for (int h = 0; h < HASH_COUNT; h++) {
        hash_pow[h].resize(s.size() + 1);
        hash_pow[h][0] = 1;
        for (int i = 1; i <= (int) s.size(); i++) {
            hash_pow[h][i] = (hash_pow[h][i - 1] * HASH_MULT[h]) % HASH_P;
        }

        p_hash[h].resize(s.size() + 1);
        p_hash[h][0] = 0;

        for (int i = 0; i < (int) s.size(); i++) {
            p_hash[h][i + 1] = ((p_hash[h][i] * HASH_MULT[h]) % HASH_P + s[i]) % HASH_P;
        }
    }
}

// must call prepare_hashes
// Returns the hash value for the substring [start, end] (inclusive on both ends)
hash_t segment_hash(int start, int end, int h) {
    int length = end - start + 1;
    hash_t value = p_hash[h][end + 1] + HASH_P - hash_pow[h][length] * p_hash[h][start] % HASH_P;
    return value >= HASH_P ? value - HASH_P : value;
}

// must call prepare_hashes
hash_t combined_hash(int start, int end) {
    // assert(HASH_COUNT == 2);
    return segment_hash(start, end, 0) + (segment_hash(start, end, 1) << 32);
}
```

It was based on: https://usaco.guide/gold/hashing?lang=cpp and https://codeforces.com/blog/entry/61587?#comment-455289 (https://codeforces.com/contest/1003/submission/42357469)

Also, I tested it in https://dmoj.ca/problem/ccc20s3 -> https://dmoj.ca/submission/6930048.

