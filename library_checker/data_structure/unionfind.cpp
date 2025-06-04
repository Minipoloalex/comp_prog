#include <bits/stdc++.h>
using namespace std;

class dsu {
    vector<int> parent, rnk;
public:
    dsu(int n) {
        parent.resize(n);
        rnk.assign(n, 1);
        iota(parent.begin(), parent.end(), 0);
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
    }
};

void solve() {
    int n, q;
    cin >> n >> q;
    dsu d(n);
    while (q--) {
        int ti, ui, vi;
        cin >> ti >> ui >> vi;
        if (ti == 0) {
            d.unite(ui, vi);
        }
        else {
            assert(ti == 1);
            cout << (d.get(ui) == d.get(vi) ? 1 : 0) << '\n';
        }
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
