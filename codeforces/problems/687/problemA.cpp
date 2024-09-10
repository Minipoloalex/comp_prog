#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;

const int MAX_N = int(1e5) + 10;
vi el[MAX_N];
vi vis;

bool bipartite(int u, int c) {
    vis[u] = c;
    for (int v: el[u]) {
        if (vis[v] == c) {
            return false;
        }
        else if (vis[v] == -1) {
            if (!bipartite(v, 1 - c)) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int n, m;
    cin >> n >> m;
    vis.assign(n, -1);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        el[u].push_back(v);
        el[v].push_back(u);
    }
    bool result = true;
    for (int i = 0; i < n; i++) {
        if (vis[i] == -1) result &= bipartite(i, 1);
    }
    if (!result) cout << "-1\n";
    else {
        auto print_ans = [&](int value) {
            vi ans;
            for (int i = 0; i < n; i++) {
                if (vis[i] == value && !el[i].empty()) ans.push_back(i + 1);
            }
            cout << ans.size() << '\n';
            for (int u: ans) {
                cout << u << " ";
            }
            cout << '\n';
        };
        print_ans(0);
        print_ans(1);
    }
    return 0;
}
