#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;

class dsu {
public:
    int n; vector<int> p;

    dsu(int _n) : n(_n), p(_n, -1) {}

    int set(int x) {
        if (p[x] < 0) return x;
        return p[x] = set(p[x]);
    }

    bool same(int x, int y) {
        return set(x) == set(y);
    }

    int size(int x) {
        return -p[set(x)];
    }

    void unite(int x, int y) {
        int px = set(x), py = set(y);
        if (px == py) return;
        if (size(px) < size(py)) swap(px, py);
        p[px] += p[py];
        p[py] = px;
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    vvi startcnt(n, vi(11)), endcnt(n, vi(11));
    while (m--) {
        int ai, di, ki;
        cin >> ai >> di >> ki;
        ai--;
        startcnt[ai][di]++;
        endcnt[ai + ki * di][di]++;
    }
    dsu uf(n);
    vvi dp(n, vi(11));
    for (int i = 0; i < n; i++) {
        for (int d = 1; d <= 10; d++) {
            int prevcnt = 0;
            int p = -1;
            if (i - d >= 0) {
                // can access previous node
                prevcnt = dp[i - d][d] - endcnt[i - d][d];
                p = uf.set(i - d);
            }
            dp[i][d] = prevcnt + startcnt[i][d];
            if (prevcnt > 0 && p != -1) {
                uf.unite(i, p);
            }
        }
    }
    int ans = 1;
    for (int i = 1; i < n; i++) {
        if (!uf.same(0, i)) {
            uf.unite(0, i);
            ans++;
        }
    }
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
