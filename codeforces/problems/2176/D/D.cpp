#include <bits/stdc++.h>
using namespace std;

const int64_t MOD = 998244353;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int64_t> a(n);
    for (auto &x: a) cin >> x;

    vector<int64_t> avals = a;
    sort(avals.begin(), avals.end());
    avals.erase(unique(avals.begin(), avals.end()), avals.end());
    auto get_aid = [&](int64_t aval) {
        auto it = lower_bound(avals.begin(), avals.end(), aval);
        if (it == avals.end() || *it != aval) return -1;
        return int(it - avals.begin());
    };
    vector<int64_t> w(avals.size());

    vector<vector<pair<int,int>>> g(n);
    vector<vector<pair<int,int>>> rev(n);
    vector<int64_t> ew(m, 1);
    for (int j = 0; j < m; j++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        g[u].emplace_back(v, j);
        rev[v].emplace_back(u, j);
    }

    vector<int> aid_want(m);
    vector<int> node_aid(n);
    for (int u = 0; u < n; u++) {
        node_aid[u] = get_aid(a[u]);
        for (auto [v, j]: g[u]) {
            aid_want[j] = get_aid(a[v] - a[u]); // what we want from a[p]
        }
    }

    int64_t ans = 0;
    // official editorial: instead of doing at most 90 (since fib(90) ~= 1e18) iterations
    // we could instead order the edges from heaviest to smallest and then handle them in that order
    // since smaller edges can't benefit from heavier ones (weight is node value)

    // the log optimization is required (the coordinate compression)
    // the others are not (vectors outside loop), but do help very slightly
    vector<int64_t> newew(m);
    vector<int> ids; ids.reserve(n);
    while (true) {
        int64_t toadd = accumulate(ew.begin(), ew.end(), 0LL);
        ans += toadd;
        ans %= MOD;
        if (toadd == 0) break;

        for (int j = 0; j < m; j++) newew[j] = 0;

        for (int u = 0; u < n; u++) {
            // p -> u -> v
            for (auto &[v, j]: g[u]) {
                int idwant = aid_want[j]; // get_aid(a[v] - a[u]); // what we want from a[p]
                if (idwant != -1) {
                    w[idwant] += ew[j];
                    if (w[idwant] >= MOD) w[idwant] -= MOD;

                    ids.push_back(idwant); // to reset later
                }
            }
            for (auto &[p, j]: rev[u]) {
                int idval = node_aid[p]; // get_aid(a[p]);
                newew[j] += w[idval];
                if (newew[j] >= MOD) newew[j] -= MOD;
            }
            for (int id: ids) {
                w[id] = 0;
            }
            ids.clear();
        }
        swap(ew, newew);
    }
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
