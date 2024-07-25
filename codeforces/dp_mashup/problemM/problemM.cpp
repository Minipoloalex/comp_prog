#include <bits/stdc++.h>
using namespace std;

typedef pair<int16_t, int> ii;
vector<ii> rev[5000];

int64_t dp[5001][5001];
int16_t p[5001][5001];

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);

    int16_t n, m;
    int T;
    cin >> n >> m >> T;
    // cout << T << endl;
    for (int i = 0; i < m; i++) {
        int16_t ui, vi;
        int ti;
        cin >> ui >> vi >> ti;
        // cout << ti << endl;
        ui--; vi--;
        rev[vi].emplace_back(ui, ti);
    }

    memset(dp, -1, sizeof dp);
    memset(p, -1, sizeof p);

    auto func = [&](int16_t u, int16_t len, auto &&self) -> int64_t {
        if (len == 0) {
            if (u == 0) return 0;
            return 1e16;
        }

        int64_t &ans = dp[u][len];
        if (ans != -1) return ans;

        int64_t curr = 1e15;
        for (auto &[v, w]: rev[u]) {
            int64_t cost = w + self(v, len - 1, self);
            if (cost < 0) while(1);

            if (cost < curr) {
                curr = cost;
                p[u][len] = v;
            }
        }
        ans = curr;
        return ans;
    };

    int ans = 0;
    for (int16_t i = 1; i < n; i++) {
        int64_t curr = func(n - 1, i, func);
        if (curr <= T) {
            ans = i + 1;
        }
    }
    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j < n; j++) {
    //         cout << dp[i][j] << " ";
    //     }
    //     cout << '\n';
    // }
    // cout << '\n';
    // for (int j = 0; j < n; j++) {
    //     cout << dp[n - 1][j] << " ";
    // }
    // cout << '\n';

    vector<int> path;
    int curr_vertex = n - 1;
    int curr_length = ans;
    while (curr_length > 0) {
        path.push_back(curr_vertex);
        curr_length--;
        // cout << curr_vertex << " " << curr_length << " " << p[curr_vertex][curr_length] << '\n';
        curr_vertex = p[curr_vertex][curr_length];
    }
    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j < n; j++) {
    //         cout << p[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    reverse(path.begin(), path.end());

    cout << ans << '\n';
    for (int v: path) {
        cout << v + 1 << " ";
    }
    cout << '\n';
    return 0;
}
