#include <bits/stdc++.h>
using namespace std;

#define all(v) (v).begin(),(v).end()

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> has_edges_one(n + 1);
    vector<array<int,3>> ans;
    while (m--) {
        int u, v;
        cin >> u >> v;
        if (u > v) swap(u, v);
        if (u == 1) {
            has_edges_one[v] ^= 1;
        }
        else {
            ans.push_back({1,u,v});
            has_edges_one[u] ^= 1;
            has_edges_one[v] ^= 1;
        }
    }
    if (accumulate(all(has_edges_one), 0) > 0) {
        int id_with_edge = -1;
        for (int i = 1; i <= n; i++) {
            if (has_edges_one[i]) {
                id_with_edge = i;
                break;
            }
        }
        assert(id_with_edge != -1);
        for (int i = 2; i <= n; i++) {
            if (!has_edges_one[i]) {
                ans.push_back({1, i, id_with_edge});
                id_with_edge = i;
            }
        }
    }
    cout << ans.size() << '\n';
    for (auto &[a, b, c]: ans) {
        cout << a << " " << b << " " << c << '\n';
    }
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
