#include <bits/stdc++.h>
using namespace std;

int n;
vector<vector<int>> g;
vector<int> curadj;

int cc_diff(int adj) {
    if (adj == 0) return -1;
    if (adj == 1) return 0;
    return adj - 1;
}

void solve() {
    cin >> n;
    g.assign(n, vector<int>());
    curadj.resize(n);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--;b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    multiset<int> ms;
    for (int i = 0; i < n; i++) {
        curadj[i] = int(g[i].size());
        ms.insert(curadj[i]);
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
        ms.erase(ms.find({curadj[i]}));
        for (int o: g[i]) {
            ms.erase(ms.find({curadj[o]}));
            curadj[o]--;
            ms.insert(curadj[o]);
        }
        int mx_adj = *(--ms.end());
        ans = max(ans, 1 + cc_diff(curadj[i]) + cc_diff(mx_adj));

        for (int o: g[i]) {
            ms.erase(ms.find({curadj[o]}));
            curadj[o]++;
            ms.insert(curadj[o]);
        }
        ms.insert(curadj[i]);
    }
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
