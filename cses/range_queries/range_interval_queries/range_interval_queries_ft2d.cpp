#include <bits/stdc++.h>
using namespace std;

#define sz(v) int((v).size())
#define all(v) (v).begin(), (v).end()

typedef long long ll;
typedef vector<int> vi;

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
};

// answers on [0, pos) for both X and Y
struct FT2 {
	vector<vi> ys; vector<FT> ft;
	FT2(int limx) : ys(limx) {}
	void fakeUpdate(int x, int y) {
		for (; x < sz(ys); x |= x + 1) ys[x].push_back(y);
	}
	void init() {
		for (vi& v : ys) sort(all(v)), ft.emplace_back(sz(v));
	}
	int ind(int x, int y) {
		return (int)(lower_bound(all(ys[x]), y) - ys[x].begin()); }
	void update(int x, int y, ll dif) {
		for (; x < sz(ys); x |= x + 1)
			ft[x].update(ind(x, y), dif);
	}
	ll query(int x, int y) {
		ll sum = 0;
		for (; x; x &= x - 1)
			sum += ft[x-1].query(ind(x-1, y));
		return sum;
	}
};
void solve() {
    int n, q;
    cin >> n >> q;
    FT2 ft(n);
    vector<int> x(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i];
        ft.fakeUpdate(i, x[i] - 1);
    }
    ft.init();
    for (int i = 0; i < n; i++) {
        ft.update(i, x[i] - 1, 1);  // because queries on FT are [0, pos) (on X and Y)
    }
    while (q--) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        int ans = int(ft.query(b, d) - ft.query(a - 1, d) - ft.query(b, c - 1) + ft.query(a - 1, c - 1));
        cout << ans << '\n';
    }
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
