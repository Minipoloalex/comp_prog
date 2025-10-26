#include <bits/stdc++.h>
using namespace std;

/**
 * Description: Computes partial sums a[0] + a[1] + ... + a[pos - 1], and updates single elements a[i],
 * taking the difference between the old and new value.
 * Time: Both operations are O(log N).
 */

using ll = long long;
#define sz(v) int((v).size())

const int64_t MOD = int64_t(1e9) + 7;

struct FT {
	vector<ll> s;
	FT(int n) : s(n) {}
	void update(int pos, ll dif) { // a[pos] += dif
		for (; pos < sz(s); pos |= pos + 1) {
            s[pos] += dif;
            s[pos] %= MOD;
        }
	}
	ll query(int pos) { // sum of values in [0, pos)
		ll res = 0;
		for (; pos > 0; pos &= pos - 1) {
            res += s[pos-1];
        }
        res %= MOD;
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
void print(vector<vector<int64_t>> arr) {
    for (int i = 0; i < arr.size(); i++) {
        for (int j = 0; j < arr[i].size(); j++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
}
void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto &ai: a) cin >> ai;
    vector<FT> rows(n+1, FT(n+1));
    vector<FT> cols(n+1, FT(n+1));
    vector<vector<int64_t>> cnts(n+1, vector<int64_t>(n+1, 0));
    cnts[0][0] = 1;
    rows[0].update(0, 1);
    cols[0].update(0, 1);
    for (int i = 0; i < n; i++) {
        for (int x = 0; x <= a[i]; x++) {
            // int64_t aux = rows[x].query(a[i]+1);    // [0, ai]
            int64_t aux1 = rows[x].query(min(x, a[i]+1));// all go to cnts[a[i],a[j]];
            int64_t aux2 = rows[x].query(a[i]+1) - aux1; // [x, a[i]]

            cnts[a[i]][x] += aux2;
            cnts[a[i]][x] %= MOD;

            rows[x].update(a[i], aux2);
            cols[a[i]].update(x, aux2);
        }
        for (int x = a[i] + 1; x <= n; x++) {
            int64_t aux = rows[x].query(a[i]+1);    // [0, ai]
            cnts[a[i]][x] += aux;
            cnts[a[i]][x] %= MOD;

            rows[x].update(a[i], aux);
            cols[a[i]].update(x, aux);
        }
        for (int aj = 0; aj < a[i]; aj++) { // aj <= a[i] ?
            // x in [a[j]+1, n]
            int64_t aux = cols[aj].query(a[i]+1) - cols[aj].query(aj+1);
            cnts[a[i]][aj] += aux;
            cnts[a[i]][aj] %= MOD;

            rows[aj].update(a[i], aux);
            cols[a[i]].update(aj, aux);
        }
        for (int aj = a[i]+1; aj <= n; aj++) { // a[j] > a[i]
            int64_t aux = cols[aj].query(a[i]+1); // [0, ai]
            // place on [a[i]][aj];
            cnts[a[i]][aj] += aux;
            cnts[a[i]][aj] %= MOD;

            cols[a[i]].update(aj, aux);
            rows[aj].update(a[i], aux);
        }
        // print(cnts);
        // cout << endl;
    }
    int64_t ans = 0;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            ans += cnts[i][j];
        }
        ans %= MOD;
    }
    cout << (ans + MOD) % MOD << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
