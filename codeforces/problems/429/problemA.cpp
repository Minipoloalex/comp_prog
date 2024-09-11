#include <bits/stdc++.h>
using namespace std;

const int MAX_N = int(1e5) + 10;
vector<int> el[MAX_N];

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int n;
    cin >> n;
    
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--;v--;
        el[u].push_back(v);
        el[v].push_back(u);
    }

    vector<int> a(n), goal(n), vis(n, 0);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> goal[i];

    vector<int> nodes;
    auto dfs = [&](int u, bool should_flip, bool prev_flipped, auto &&self) -> int {
        int ans = 0;
        int value = should_flip ? 1 - a[u] : a[u];
        bool had_to_flip = value != goal[u];
        // cout << u << " " << boolalpha << should_flip << " " << prev_flipped << " " << had_to_flip << " " << a[u] << " " << value << " " << goal[u] << endl;


        bool nshould_flip = prev_flipped;
        bool nprev_flipped = should_flip ^ had_to_flip;

        if (had_to_flip) {
            nodes.push_back(u + 1);
            ans++;
        }

        vis.at(u) = 1;
        for (int v: el[u]) {
            if (!vis.at(v)) {
                // cout << u << " " << v << endl;
                ans += self(v, nshould_flip, nprev_flipped, self);
            }
        }
        return ans;
    };
    int ans = dfs(0, false, false, dfs);
    cout << ans << '\n';
    for (int node: nodes) {
        cout << node << '\n';
    }
    return 0;
}
