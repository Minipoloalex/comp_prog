#include <bits/stdc++.h>
using namespace std;

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


void solve() {
    string s;
    cin >> s;
    int n = int(s.size());
    s += s; // wrap-around
    prepare_hashes(s);

    auto smaller = [&](int i, int j) {
        int lo = 0, hi = n - 1;
        while (lo < hi) {
            int m = lo + (hi - lo) / 2;
            if (combined_hash(i, i + m) == combined_hash(j, j + m)) {
                lo = m + 1;
            }
            else {
                hi = m;
            }
        }
        return s[i + lo] < s[j + lo];
    };
    int ans = 0;
    for (int i = 1; i < n; i++) {
        if (smaller(i, ans)) {
            ans = i;
        }
    }
    cout << s.substr(ans, n - ans) + s.substr(0, ans) << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    solve();
    return 0;
}
