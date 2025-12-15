#include <bits/stdc++.h>
using namespace std;

const int MAX_N = int(2e5);
bitset<MAX_N+1> bs;

void solve() {
    int n, k;
    cin >> n >> k;
    vector<vector<int>> g(n);
    for (int i = 1; i < n; i++) {
        int pi; cin >> pi; pi--;
        g[pi].push_back(i);
    }
    vector<int> dep(n);
    function<void(int,int)> dfs = [&](int u, int d) {
        dep[u] = d;
        for (int v: g[u]) {
            dfs(v, d + 1);
        }
    };
    dfs(0,0);
    vector<int> arr; arr.reserve(n);
    vector<int> cnt(n);
    int mn = INT_MAX;
    for (int i = 0; i < n; i++) {
        cnt[dep[i]]++;
        if (g[i].empty()) {
            mn = min(mn, dep[i]);
        }
    }
    for (int i = 0; i <= mn; i++) {
        arr.push_back(cnt[i]);
    }
    for (int i = mn+1; i < n; i++) {
        if (cnt[i]) {
            for (int j = 0; j < cnt[i]; j++) arr.push_back(1);
        }
    }
    vector<int> freq(n+1);
    for (auto &v: arr) {
        freq[v]++;
    }
    // size: sqrt(n) * log2(n)?
    // actually, editorial says it's sqrt(n) only
    vector<int> vals; vals.reserve(n);
    for (int i = 1; i <= n; i++) {
        if (freq[i]) {
            for (int j = 0; freq[i]; j++) {
                int c = min(freq[i], 1 << j);
                freq[i] -= c;
                vals.emplace_back(i * c);
            }
        }
    }
    bs.reset();
    bs[0] = 1;
    for (int v: vals) {
        // should consider multiple test cases: sqrt(sum) != sum(sqrt)
        // complexity is fine here
        bs |= bs << v;
    }
    int ans = bs[k] ? mn + 1 : mn;
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
