#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
using ll = long long;
#define sz(v) int((v).size())

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

vector<int> posppl, posstops;

void solve() {
    int64_t n, b, r, w;
    cin >> n >> b >> r >> w;
    vector<int> d(b), t(n);
    for (auto &di: d) cin >> di;
    for (auto &ti: t) cin >> ti;
    // sort(t.rbegin(), t.rend());
    vector<int64_t> pref(b + 1);
    for (int i = 1; i <= b; i++) {
        pref[i] = pref[i-1] + d[i-1];
    }
    vector<int> cntss(b+1);
    FT cntppl(b+1), cntstops(b+1);
    auto good = [&](int64_t _tl) {
        int i = 0;
        while (i < n) {
            if (i > 0) _tl -= r;
            int64_t tl = _tl;

            int64_t cur = 0;
            int j;
            int mx = 0;

            // ordered_set<int> small_s;
            // ordered_set<pair<int,int>> s;
            for (j = i; j < n; j++) {
                int64_t smaller = cntstops.query(t[j]);

                // int smaller = s.order_of_key({t[j], 0});
                int64_t bigger = cur - cntppl.query(t[j]+1);

                int64_t to_add = 2*w;
                to_add += smaller*2*w;
                if (cntstops.query(t[j] + 1) - smaller == 0) {
                    to_add += bigger*2*w;
                }
                if (t[j] > mx) {
                    to_add += pref[t[j]] - pref[mx];
                }
                if (tl - to_add < 0) {
                    break;
                }

                if (cntss[t[j]]++ == 0) {
                    cntstops.update(t[j], +1);
                    posstops.push_back(t[j]);
                }
                cntppl.update(t[j], +1);
                posppl.push_back(t[j]);

                mx = max(mx, t[j]);
                cur++;
                tl -= to_add;
            }
            for (int p: posppl) {
                cntppl.update(p, -1);
            }
            for (int p: posstops) {
                cntss[p] = 0;
                cntstops.update(p, -1);
            }
            posppl.clear();
            posstops.clear();
            if (j == i) return false;
            i = j;
        }
        return true;
    };
    int64_t lo = 0, hi = int64_t(1e18);
    while (lo < hi) {
        int64_t med = lo + (hi - lo) / 2;
        if (good(med)) {
            hi = med;
        }
        else {
            lo = med + 1;
        }
    }
    cout << lo << '\n';
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
