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

//  z[i] is the LCP (longest common prefix) of s and s.substr(i) (suffix of S starting at i: s[i:]).
// For S = "aabxaayaab", Z = [10, 1, 0, 0, 2, 1, 0, 3, 1, 0] (same size as S)
vector<int> z_function(const string &s) {
	vector<int> z(s.size());
	z[0] = (int) s.size();

	int l = 0, r = 0;
	for (int i = 1; i < (int) s.size(); i++) {
		z[i] = max(0, min(z[i - l], r - i + 1));
		while (i + z[i] < (int) s.size() && s[z[i]] == s[i + z[i]]) {
			l = i;
			r = i + z[i];
			z[i]++;
		}
	}
	return z;
}

const int64_t MOD = 998244353;
const int MAX_N = int(1e6);

void solve() {
    string a, l, r;
    cin >> a >> l >> r;
    int n = sz(a), L = sz(l), R = sz(r);
    vector<int> zl = z_function(l + "#" + a), zr = z_function(r + "#" + a);

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

        // the hashing solution literally does this (find LCP and then compare character after it to compare the two strings)
        int leftZ = zl[i + L + 1];
        if (leftZ < L && a[i + leftZ] < l[leftZ]) {
            // smaller (a[i:i+L-1] < l)
            lef++;
        }
        if (rig == i + R - 1) { // if R wasn't cut off (if it was, then for sure it's smaller than r)
            int rightZ = zr[i + R + 1];
            if (rightZ < R && a[i + rightZ] > r[rightZ]) {
                rig--;  // bigger (a[i:i+R-1] > r)
            }
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
