#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define sz(v) int(v.size())

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

void solve() {
    int x, y, n, d;
    cin >> x >> y >> n >> d;
    vector<vector<int>> g(y + 2, vector<int>(x + 2));
    for (int k = 0; k < n; k++) {
        int x1,x2,y1,y2;
        cin >> x1 >> x2 >> y1 >> y2;
        x1++;x2++;y1++;y2++;

        // instead of using prefix sums, could've just done this (since there's no overlap)
        // for (int i = y1; i < y2; i++) {
        //     for (int j = x1; j < x2; j++) {
        //         g[i][j] = 1;
        //     }
        // }
        g[y1][x1]++;
        g[y2][x1]--;
        g[y1][x2]--;
        g[y2][x2]++;
    }
    n = 0;

    // they say no overlaps, but I missed that, whoops... I guess these are fine
    // used prefix sums to build the rectangles
    for (int j = 1; j <= x; j++) {
        for (int i = 1; i <= y; i++) {
            g[i][j] += g[i-1][j];
        }
    }
    for (int i = 1; i <= y; i++) {
        for (int j = 1; j <= x; j++) {
            g[i][j] += g[i][j-1];
        }
    }
    for (int i = 0; i <= y + 1; i++) {
        for (int j = 0; j <= x + 1; j++) {
            if (i == 0 || j == 0 || i == y + 1 || j == x + 1) g[i][j] = 0;
            else g[i][j] = max(0, min(1, g[i][j]));
        }
    }
    // end of prefix sums

    vector<vector<pair<int,int>>> updates(y + 1);
    for (int j = 1; j <= x; j++) {
        for (int i = y; i >= 1; i--) {
            if (g[i][j] == 0) {
                g[i][j] = g[i+1][j] + 1;
            }
            else {
                g[i][j] = 0;
            }
            if (g[i][j] > 0) {
                updates[g[i][j]].emplace_back(i, j);
            }
        }
    }
    // for (int i = 1; i <= y; i++) {
    //     for (int j = 1; j <= x; j++) {
    //         cout << g[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    vector<vector<pair<int,int>>> qs(y + 1);
    vector<int64_t> ans(d);
    for (int i = 0; i < d; i++) {
        int xsize, ysize;
        cin >> xsize >> ysize;
        qs[ysize].emplace_back(xsize, i);
    }

    FT cnt(x + 1), sum(x + 1);
    auto suffix = [&](int l, FT &ft) { // [l, X]
        return ft.query(x + 1) - ft.query(l);
    };

    auto remove = [&](int SZ) {
        cnt.update(SZ, -1);
        sum.update(SZ, -(SZ + 1));
    };
    auto add = [&](int SZ) {
        cnt.update(SZ, +1);
        sum.update(SZ, +(SZ + 1));
    };
    auto query = [&](int W) -> int64_t {
        return suffix(W, sum) - W * suffix(W, cnt);
    };
    vector<vector<int>> lef(y + 2, vector<int>(x + 2, 0)), rig = lef, siz = lef;
    for (int h = y; h >= 1; h--) {
        for (auto &[i, j]: updates[h]) {
            siz[i][j] = 1;
            int left = j;
            int right = j;
            if (siz[i][j-1] > 0) {
                remove(siz[i][j-1]);
                siz[i][j] += siz[i][j-1];
                left = lef[i][j-1];
            }
            if (siz[i][j+1] > 0) {
                remove(siz[i][j+1]);
                siz[i][j] += siz[i][j+1];
                right = rig[i][j+1];
            }

            rig[i][left] = right;
            lef[i][right] = left;

            siz[i][left] = siz[i][right] = siz[i][j];
            add(siz[i][j]);
        }
        for (auto &[w, origidx]: qs[h]) {
            // cout << origidx << " ";
            ans[origidx] = query(w);
        }
    }
    for (int64_t v: ans) {
        cout << v << '\n';
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
