#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<vector<int>> g(n);
    vector<int> cnt(n, 0);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--;b--;
        g[a].push_back(b);
        g[b].push_back(a);
        cnt[a]++;
        cnt[b]++;
    }
    set<pair<int,int>> pq;
    for (int i = 0; i < n; i++) {
        if (g[i].size() == 1) { // or cnt[i] == 1
            pq.emplace(1, i);
        }
    }
    vector<int> vis(n, 0), total(n, 1);
    while (!pq.empty()) {
        auto [cur, u] = *pq.begin();
        pq.erase(pq.begin());
        vis[u] = true;
        for (int v: g[u]) { 
            if (!vis[v]) {
                if (total[v] < total[u]) {
                    cout << "NO\n";
                    return;
                }
                total[v] += total[u];
                cnt[v]--;

                if (cnt[v] == 1) {  // only parent
                    pq.emplace(total[v], v);
                }
            }
        }
    }
    cout << "YES\n";
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
