#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define sz(u) int(u.size())

struct FT {
	vector<ll> s;
	FT(int n) : s(n) {}
	void update(int pos, ll dif) { // a[pos] += dif
		for (; pos < sz(s); pos |= pos + 1) s[pos] += dif;
	}
	ll query(int pos) { // sum of values in [0, pos)
		ll res = 0;
		for (; pos > 0; pos &= pos - 1) res += s[pos-1];
		return res;
	}
	int lower_bound(ll sum) {// min pos st sum of [0, pos] >= sum
		// Returns n if no sum is >= sum, or -1 if empty sum is.
		if (sum <= 0) return -1;
		int pos = 0;
		for (int pw = 1 << 25; pw; pw >>= 1) {
			if (pos + pw <= sz(s) && s[pos + pw-1] < sum)
				pos += pw, sum -= s[pos-1];
		}
		return pos;
	}
};

typedef uint64_t hash_t;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int HASH_COUNT = 2;
const hash_t HASH_P = (uint32_t) -13337; // 4294953959
uniform_int_distribution<hash_t> MULT_DIST(int64_t(0.25 * HASH_P), int64_t(0.75 * HASH_P));
const hash_t HASH_MULT[HASH_COUNT] = {MULT_DIST(rng), MULT_DIST(rng)};
vector<hash_t> hash_pow[HASH_COUNT];    // pow[i] contains B^i % M

void prepare_hash_pow(int MAX_SIZE) { // O(MAX_SIZE)
    for (int h = 0; h < HASH_COUNT; h++) {
        hash_pow[h].resize(MAX_SIZE + 1);
        hash_pow[h][0] = 1;
        for (int i = 1; i <= MAX_SIZE; i++) {
            hash_pow[h][i] = (hash_pow[h][i - 1] * HASH_MULT[h]) % HASH_P;
        }
    }
}

/**
 * Usage:
 *  string s;
 *  s_hash hsh(s);
 *  hsh.combined_hash(0, n - 1)
 */
struct s_hash {
private:
    // p_hash[i] is the hash of the first i characters of the given string
    // Prefix [l, r], with sz = r - l + 1
    // sl * B^sz-1 + s(l + 1) * B^sz-2 + ... + sr * B^0
    vector<hash_t> p_hash[HASH_COUNT];
    int size = 0;

    void prepare_hashes(const string &s) {  // O(s.size())
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

public:
    s_hash() {} // should not be used
    s_hash(const string &s) {
        size = (int) s.size();
        prepare_hashes(s);
    }

    // must call prepare_hashes
    // inclusive: [start, end], 0-indexed
    hash_t combined_hash(int start, int end) {
        // assert(HASH_COUNT == 2);
        return segment_hash(start, end, 0) + (segment_hash(start, end, 1) << 32);
    }
};

bool compare(s_hash &a, s_hash &other, int st, int end, string &aa, string &oo) {
    // return a[st:end] < other
    int lo = st, hi = end;
    while (lo < hi) {
        int m = lo + (hi - lo) / 2;
        if (a.combined_hash(st, m) == other.combined_hash(0, m - st)) {
            lo = m + 1;
        }
        else {
            hi = m;
        }
    }
    return aa[lo] < oo[lo - st];
}

const int64_t MOD = 998244353;
const int MAX_N = int(1e6);

void solve() {
    string a, l, r;
    cin >> a >> l >> r;
    int n = sz(a), L = sz(l), R = sz(r);

    prepare_hash_pow(MAX_N);
    s_hash hash_a(a), hash_l(l), hash_r(r);

    FT ft(n + 1);
    vector<int64_t> dp(n + 1);  // nr of ways by starting at position i
    dp[n] = 1;
    ft.update(n, 1);

    for (int i = n - 1; i >= 0; i--) {
        int lef = i + L - 1, rig = min(i + R - 1, n - 1);
        if (lef >= n || (a[i] == '0' && l != "0")) {
            continue;   // dp already 0
        }
        if (a[i] == '0') {
            // we know l == "0"
            // but we need to ensure only one digit can be used (from a): to avoid leading 0s
            rig = i;
        }

        if (compare(hash_a, hash_l, i, i + L - 1, a, l)) {
            lef++;  // smaller (a[i:i+L-1] < l)
        }
        if (rig == i + R - 1 && !compare(hash_a, hash_r, i, i + R - 1, a, r)
            && hash_a.combined_hash(i, i + R - 1) != hash_r.combined_hash(0, R - 1)) {
            rig--;  // not smaller and not equal (a[i:i+R-1] > r)
        }
        if (lef <= rig) {
            // [lef, rig] corresponds to valid strings for this step
            // so, we should query sum of dp in interval: [lef + 1, rig + 1]
            dp[i] = (ft.query(rig + 2) - ft.query(lef + 1)) % MOD;
        }
        ft.update(i, dp[i]);    // ft can ignore mod, because it's int64_t and every pos < 1e9
    }
    cout << dp[0] << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
