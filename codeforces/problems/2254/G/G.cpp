#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &x: a) cin >> x;
    vector<vector<int>> g(n);
    for (int i = 1; i < n; i++) {
        int pi;
        cin >> pi;
        pi--;
        g[pi].push_back(i);
    }

    using pq = priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>;
    vector<pq> pqs(n);
    function<void(int)> dfs = [&](int u) {
        int mx = 0;
        int mxid = -1;
        for (int v: g[u]) {
            dfs(v);
            if (int(pqs[v].size()) > mx) {
                mx = int(pqs[v].size());
                mxid = v;
            }
        }
        if (g[u].empty()) { // leaf
            pqs[u].emplace(a[u], u);
        }
        else {
            // not a leaf: must merge things
            swap(pqs[u], pqs[mxid]);
            for (int v: g[u]) {
                if (v == mxid) continue;
                while (!pqs[v].empty()) {
                    pqs[u].push(pqs[v].top());
                    pqs[v].pop();
                }
            }
            auto [mnval, mnid] = pqs[u].top();
            if (a[u] > mnval) {
                pqs[u].pop();
                pqs[u].emplace(a[u], u);
            }
        }
    };
    dfs(0);

    vector<int64_t> ans(n);
    int64_t base = 0;
    vector<int> used(n);
    pq &mxs = pqs[0];
    int l = int(mxs.size());
    while (!mxs.empty()) {
        auto [val, id] = mxs.top();
        mxs.pop();
        used[id] = 1;
        base += val;
    }
    vector<int> notused; notused.reserve(n);
    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            notused.push_back(a[i]);
        }
    }
    sort(notused.begin(), notused.end());
    int64_t curans = base;
    for (int k = 1; k < l; k++) {
        cout << "-1 ";
    }
    for (int k = l; k <= n; k++) {
        cout << curans << " \n"[k == n];
        if (k < n) {
            curans += notused.back();
            notused.pop_back();
        }
    }
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
