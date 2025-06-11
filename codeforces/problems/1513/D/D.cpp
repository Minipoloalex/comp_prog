#include <bits/stdc++.h>
using namespace std;


class ufds {
    int n;
    vector<int> rnk, p;
public:
    ufds(int sz) {
        n = sz;
        rnk.assign(n, 1);
        p.resize(n);
        iota(p.begin(), p.end(), 0);
    }
    int get(int a) {
        return p[a] = (p[a] == a ? a : get(p[a]));
    }
    bool same_set(int a, int b) {
        return get(a) == get(b);
    }
    void unite(int a, int b) {
        int pa = p[a];
        int pb = p[b];
        if (pa == pb) return;
        if (rnk[pa] < rnk[pb]) swap(pa, pb);
        p[pb] = pa;
        if (rnk[pa] == rnk[pb]) rnk[pa]++;
    }
};


void solve() {
    int n, p;
    cin >> n >> p;
    vector<int> a(n);
    vector<pair<int,int>> sorted(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        sorted[i] = {a[i], i};
    }
    sort(sorted.begin(), sorted.end());
    int64_t ans = 0;
    ufds dsu(n);
    for (auto &[ai, i]: sorted) {
        if (ai >= p) {
            break;
        }
        for (int r = i + 1; r < n; r++) {
            if (dsu.same_set(i, r)) break;  // no point in continuing (also, other minimum was smaller/better)
            if (gcd(ai, a[r]) != ai) break;
            ans += ai;
            dsu.unite(i, r);
        }
        for (int l = i - 1; l >= 0; l--) {
            if (dsu.same_set(i, l)) break;
            if (gcd(ai, a[l]) != ai) break;
            ans += ai;
            dsu.unite(i, l);
        }
    }
    for (int i = 0; i < n; i++) {
        // this is weird, but it's equivalent (there are K missing edges, simply need to account for those)
        if (!dsu.same_set(0, i)) {
            dsu.unite(0, i);
            ans += p;
        }
        // otherwise, could just do this (with i < n - 1)
        // if (!dsu.same_set(i, i + 1)) {
        //     dsu.unite(i, i + 1);
        //     ans += p;
        // }
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
