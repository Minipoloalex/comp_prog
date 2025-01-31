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

void prepare_hash_pow(int MAX_SIZE) {
    for (int h = 0; h < HASH_COUNT; h++) {
        hash_pow[h].resize(MAX_SIZE + 1);
        hash_pow[h][0] = 1;
        for (int i = 1; i <= (int) MAX_SIZE; i++) {
            hash_pow[h][i] = (hash_pow[h][i - 1] * HASH_MULT[h]) % HASH_P;
        }
    }
}

struct s_hash {
    // p_hash[i] is the hash of the first i characters of the given string
    // Prefix [l, r], with sz = r - l + 1
    // sl * B^sz-1 + sl + 1 * B^sz-2 + ... + sr * B^0
    vector<hash_t> p_hash[HASH_COUNT];
    int size = 0;

    s_hash() {} // should not be used

    s_hash(const string &s) {
        size = (int) s.size();
        prepare_hashes(s);
    }

    void prepare_hashes(const string &s) {
        for (int h = 0; h < HASH_COUNT; h++) {
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
};

bool suf_equal_to_pref(s_hash &first, s_hash &second, int sz) {
    int ef = first.size - 1;
    int sf = ef - sz + 1;
    int ss = 0;
    int es = ss + sz - 1;
    return first.combined_hash(sf, ef) == second.combined_hash(ss, es);
}


const int MAX_STRING_SIZE = int(1e4);

void solve() {
    int n;
    cin >> n;
    // not required, since we only need the size of the strings
    // which is saved in struct s_hash
    vector<string> s(n);

    prepare_hash_pow(MAX_STRING_SIZE);
    vector<s_hash> hashes(n);
    for (int i = 0; i < n; i++) {
        string x;
        cin >> x;
        s[i] = x;
        hashes[i] = s_hash(x);
    }
    // need to handle strings that are substrings of others
    // otherwise, WA: https://usaco.guide/problems/cf-104048K/user-solutions

    vector<int> ids;
    for (int i = 0; i < n; i++) {
        bool substring = false;
        for (int j = 0; j < n; j++) {
            if (i == j || s[i].size() > s[j].size()) continue;

            // careful of equal strings (sorting the strings by size could be easier)
            if (s[i].size() == s[j].size() && j < i) continue;

            // i is the smallest string
            int start_i = 0;
            int end_i = int(s[i].size() - 1);
            for (int start_j = start_i, end_j = end_i; end_j < int(s[j].size()); start_j++, end_j++) {
                if (hashes[i].combined_hash(start_i, end_i) == hashes[j].combined_hash(start_j, end_j)) {
                    // i is substring of j: we don't want to work with i
                    substring = true;
                    break;
                }
            }
            if (substring) break;
        }
        if (!substring) {   // we can use it
            ids.push_back(i);   
        }
    }

    n = int(ids.size());
    for (int i = 0; i < n; i++) {
        // works because ids is sorted
        s[i] = s[ids[i]];
        hashes[i] = hashes[ids[i]];
    }
    s.resize(n);
    hashes.resize(n);
    iota(ids.begin(), ids.end(), 0);

    vector<vector<int>> common(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        string &si = s[i];
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            string &sj = s[j];
            int min_size = (int) min(si.size(), sj.size());
            for (int k = 1; k <= min_size; k++) {
                if (suf_equal_to_pref(hashes[i], hashes[j], k)) {
                    // here we can use i, j because we have not yet sorted the strings
                    // otherwise, we would have to use iidx and jidx
                    common[i][j] = k;
                }
            }
        }
    }

    // not required, since they are obviously sorted [0, 1, ..., n - 1]
    // sort(ids.begin(), ids.end());
    int64_t ans = INT64_MAX;
    do {
        int64_t cur = s[ids[0]].size();
        for (int i = 1; i < n; i++) {
            int bidx = ids[i - 1];
            int curidx = ids[i];
            string &curs = s[curidx];
            cur += curs.size() - common[bidx][curidx];
        }
        ans = min(ans, cur);
    } while (next_permutation(ids.begin(), ids.end()));
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    solve();
    return 0;
}
