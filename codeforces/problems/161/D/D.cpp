 #include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;
    vector<vector<int>> g(n);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--;b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    vector<int> par(n);
    function<void(int,int)> dfs = [&](int u, int p) {
        par[u] = p;
        for (int v: g[u]) {
            if (v != p) {
                dfs(v, u);
            }
        }
    };
    dfs(0, -1);
    vector<vector<int>> dp(n, vector<int>(k + 1, -1)), down(n, vector<int>(k + 1, -1));
    function<int(int,int)> godown = [&](int u, int ki) -> int {
        if (ki == 0) return 1;
        if (ki < 0) return 0;

        int &ans = down[u][ki];
        if (ans != -1) return ans;

        int cur_ans = 0;
        for (int v: g[u]) {
            if (v != par[u]) {
                cur_ans += godown(v, ki - 1);
            }
        }
        return ans = cur_ans;
    };
    function<int(int,int)> godp = [&](int u, int ki) -> int {
        if (ki == 0) return 1;

        int &ans = dp[u][ki];
        if (ans != -1) return ans;

        int cur_ans = godown(u, ki);
        if (par[u] != -1) {
            cur_ans += godp(par[u], ki - 1) - godown(u, ki - 2);
        }
        return ans = cur_ans;
    };
    int64_t ans = 0;
    for (int i = 0; i < n; i++) {
        ans += godp(i, k);
    }
    cout << ans / 2 << '\n';
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
