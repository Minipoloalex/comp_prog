#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int64_t> a(n);
    for (auto &ai: a) cin >> ai;
    vector<vector<int>> g(n);
    for (int i = 1; i < n; i++) {
        int pi;
        cin >> pi;
        pi--;
        g[pi].push_back(i);
    }
    int64_t ans = 0;
    vector<int64_t> toadd(n);
    // if instead of a PQ, we do a BFS down from the node we're currently in, we can get easy O(n^2)
    // because the first node we see is the best node to use (less depth)
    using T = tuple<int,int64_t,int>;   // cost (<= n), cnt (how much to add), node (descendant where to add)
    priority_queue<T,vector<T>,greater<T>> pq;
    function<int64_t(int,int)> dfsdep = [&](int u, int dep) {
        int64_t sm = 0;
        for (int v: g[u]) {
            sm += dfsdep(v, dep+1);
        }
        if (g[u].empty()) sm = INT64_MAX;
        if (a[u] < sm) {
            // can increase a[u] up to sum
            pq.emplace(dep, sm - a[u], u);
        }
        return a[u];
    };
    function<int64_t(int)> dfsprop = [&](int u) {
        int64_t cur = toadd[u];
        toadd[u] = 0;
        for (int v: g[u]) {
            cur += dfsprop(v);
        }
        a[u] += cur;
        return cur;
    };
    function<void(int)> dfs = [&](int u) {
        for (int v: g[u]) {
            dfs(v);
        }
        int64_t sm = 0;
        for (int v: g[u]) {
            sm += dfsdep(v, 1); // fills pq
        }
        if (g[u].empty()) sm = INT64_MAX;
        while (a[u] > sm) {
            auto [cost, cnt, node] = pq.top();
            pq.pop();
            int64_t val = min(a[u] - sm, cnt);
            toadd[node] += val; // or use =
            sm += val;
            ans += val*cost;
        }
        while (!pq.empty()) pq.pop();
        for (int v: g[u]) {
            dfsprop(v);
        }
    };
    dfs(0);
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
