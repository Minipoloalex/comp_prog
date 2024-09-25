#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
const int MAX_N = int(2e5) + 10;
vector<vi> el;
vi gold, p;
int n, c;

int64_t dp[MAX_N][2];

int64_t solve(int u, int w) {
    int64_t &ans = dp[u][w];
    if (ans != INT64_MAX) return ans;

    int64_t curr = 0;
    if (w == 1) curr += gold.at(u); // safeguard node u

    for (int v: el.at(u)) {
        if (p.at(u) != v) {
            p.at(v) = u;
            int64_t neigh_w = solve(v, 1);      // answer safeguarding child v
            if (w == 1) neigh_w -= 2 * c;   // picked child and parent, both are decremented by c

            int64_t neigh_wo = solve(v, 0);     // answer not safeguarding child v

            int64_t mx_neigh = max(neigh_wo, neigh_w);
            curr += mx_neigh;
        }
    }
    return ans = curr;
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t;
    cin >> t;

    while (t--) {
        cin >> n >> c;
        gold.resize(n);
        p.assign(n, -1);
        el.assign(n, vi());

        for (int i = 0; i < n; i++) cin >> gold[i];
        for (int i = 0; i < n - 1; i++) {
            int u, v;
            cin >> u >> v;
            u--;v--;
            el[u].push_back(v);
            el[v].push_back(u);
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < 2; j++) {
                dp[i][j] = INT64_MAX;
            }
        }

        int64_t ans_w = solve(0, 1);
        int64_t ans_wo = solve(0, 0);
        int64_t ans = max(ans_wo, ans_w);

        cout << ans << '\n';
    }
    return 0;
}
