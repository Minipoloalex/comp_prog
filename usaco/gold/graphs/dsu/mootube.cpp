#include <bits/stdc++.h>
using namespace std;

class dsu {
    vector<int> parent, rnk, sz;
public:
    dsu(int n) {
        parent.resize(n);
        rnk.assign(n, 1);
        sz.assign(n, 1);
        iota(parent.begin(), parent.end(), 0);
    }
    int get(int i) {
        return parent[i] = (parent[i] == i ? i : get(parent[i]));
    }
    int get_sz(int i) {
        return sz[get(i)];
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
        sz[pi] += sz[pj];
    }
};


void solve() {
    int n, q;
    cin >> n >> q;
    vector<array<int,3>> e(n-1);
    for (auto &[ri, pi, qi]: e) {
        cin >> pi >> qi >> ri;
        pi--;
        qi--;
    }
    sort(e.begin(), e.end(), greater<array<int,3>>());

    vector<array<int,3>> qs(q);
    for (int i = 0; i < q; i++) {
        auto &[ki, vi, idx] = qs[i];
        cin >> ki >> vi;
        vi--;
        idx = i;
    }
    sort(qs.begin(), qs.end(), greater<array<int,3>>());

    dsu d(n);
    int eiter = 0, ne = n - 1;
    vector<pair<int,int>> ans;
    for (auto &[ki, vi, idx]: qs) {
        // add all edges <= v (other than those previously added)
        for (; eiter < ne; eiter++) {
            auto &[w, a, b] = e[eiter];
            if (w < ki) {
                break;
            }
            d.unite(a, b);
        }
        ans.emplace_back(idx, d.get_sz(vi));
    }
    sort(ans.begin(), ans.end());
    for (auto &[_, sz]: ans) {
        cout << sz - 1 << '\n';
    }
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    freopen("mootube.in", "r", stdin);
    freopen("mootube.out", "w", stdout);
    solve();
    return 0;
}
