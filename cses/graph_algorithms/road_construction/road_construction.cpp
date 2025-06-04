#include <bits/stdc++.h>
using namespace std;

class dsu {
    vector<int> parent, rnk;
    // auxiliary for this problem
    vector<int> sz; // connected components size
public:
    // auxiliary for this problem
    int ccs, cc_mx;
    dsu(int n) {
        parent.resize(n);
        iota(parent.begin(), parent.end(), 0);
        rnk.assign(n, 1);
        sz.assign(n, 1);
        cc_mx = 1;
        ccs = n;
    }
    int get(int i) {
        return parent[i] = (parent[i] == i ? i : get(parent[i]));
    }
    void unite(int i, int j) {
        int pi = get(i);    // "going to be the new parent" (swapped if necessary)
        int pj = get(j);
        if (pi == pj) return;
        if (rnk[pi] < rnk[pj]) {
            swap(pi, pj);
        }
        // rnk[pi] >= rnk[pj]
        if (rnk[pi] == rnk[pj]) rnk[pi]++;
        parent[pj] = pi;

        // auxiliary
        sz[pi] += sz[pj];
        cc_mx = max(cc_mx, sz[pi]);
        ccs--;
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    dsu d(n);
    while (m--) {
        int a, b;
        cin >> a >> b;
        a--;b--;
        d.unite(a, b);
        cout << d.ccs << " " << d.cc_mx << '\n';
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
