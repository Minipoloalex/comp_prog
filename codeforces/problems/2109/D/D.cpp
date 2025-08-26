#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m, l;
    cin >> n >> m >> l;
    vector<int> a(l);
    for (auto &ai: a) cin >> ai;
    int64_t A = accumulate(a.begin(), a.end(), 0LL);

    int smallest_odd = INT_MAX;
    for (int i = 0; i < l; i++) {
        if (a[i] % 2 == 1) {
            smallest_odd = min(smallest_odd, a[i]);
        }
    }
    int64_t maxEvenA = 0, maxOddA = 0;
    if (A % 2 == 0) {
        maxEvenA = A;
        if (smallest_odd != INT_MAX) {
            // remove smallest odd number to make the other parity
            maxOddA = maxEvenA - smallest_odd;
        }
    }
    else {
        maxOddA = A;
        if (smallest_odd != INT_MAX) {
            // remove smallest odd number to make the other parity
            maxEvenA = maxOddA - smallest_odd;
        }
    }

    vector<vector<int>> g(n);
    while (m--) {
        int u, v;
        cin >> u >> v;
        u--;v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    using S = pair<int,int64_t>;
    queue<S> q;
    vector<array<int64_t,2>> dist(n, {INT64_MAX, INT64_MAX});
    dist[0][0] = 0; // distance for source is 0 (also, it's an even distance)
    q.emplace(0, 0);
    while (!q.empty()) {
        auto [u, d] = q.front();
        q.pop();
        for (int v: g[u]) {
            if (dist[v][(d + 1) % 2] == INT64_MAX) {
                dist[v][(d + 1) % 2] = d + 1;
                q.emplace(v, d + 1);
            }
        }
    }
    string ans(n, '0');
    for (int i = 0; i < n; i++) {
        auto &[deven, dodd] = dist[i];
        if (maxEvenA >= deven) {
            ans[i] = '1';
        }
        if (maxOddA >= dodd) {
            ans[i] = '1';
        }
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
