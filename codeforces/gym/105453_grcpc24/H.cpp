#include <bits/stdc++.h>
using namespace std;


class dsu {
    vector<int> parent, sz, rnk;
    vector<bool> magical;
public:
    dsu(int n, vector<bool> &mag) {
        parent.resize(n); iota(parent.begin(), parent.end(), 0);
        rnk.assign(n, 1);
        magical = mag;
        sz.assign(n, 1);
    }
    int set(int x) {
        return parent[x] = (x == parent[x] ? x : set(parent[x]));
    }
    bool same_set(int x, int y) {
        return set(x) == set(y);
    }
    int unite(int x, int y) {
        if (same_set(x, y)) return 0;
        int px = set(x);
        int py = set(y);
        if (rnk[px] < rnk[py]) {
            swap(px, py);
        }
        parent[py] = px;
        if (rnk[px] == rnk[py]) rnk[px]++;

        int ans = 0;
        if (magical[px] && !magical[py]) {
            ans = sz[py];
        }
        else if (!magical[px] && magical[py]) {
            ans = sz[px];
        }
        sz[px] += sz[py];
        magical[px] = magical[px] || magical[py];
        return ans;
    }
};

void solve() {
    int n, m, c;
    cin >> n >> m >> c;
    vector<bool> magical(n, 0);
    for (int i = 0; i < c; i++) {
        int si;
        cin >> si;
        si--;
        magical[si] = 1;
    }
    vector<vector<int>> g(n);
    
    while (m--) {
        int a, b;
        cin >> a >> b;
        a--;b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    int Q;
    cin >> Q;
    vector<int> ql(Q);

    vector<int> inq(n, 0);
    for (auto &qi: ql) {
        cin >> qi;
        qi--;
        inq[qi]++;
    }
    reverse(ql.begin(), ql.end());
    dsu d(n, magical);
    for (int i = 0; i < n; i++) {
        if (inq[i]) continue;
        for (int v: g[i]) {
            if (inq[v]) continue;
            d.unite(i, v);
        }
    }
    vector<int> ans;
    for (int qi: ql) {
        inq[qi]--;
        int val = 0;
        if (!inq[qi]) {
            if (magical[qi]) {
                val++;
            }
            for (int v: g[qi]) {
                if (!inq[v]) {
                    val += d.unite(qi, v);
                }
            }
        }
        ans.push_back(val);
    }
    reverse(ans.begin(), ans.end());
    for (int a: ans) cout << a << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    solve();
    return 0;
}
