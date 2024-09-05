#include <bits/stdc++.h>
using namespace std;


int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int n, m;
    cin >> n >> m;

    vector<vector<int>> em(n, vector<int>(n, 0));
    vector<int> dist(n, -1);

    bool use_railways = true;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;  // bidirectional railway
        if ((u == 1 && v == n) || (u == n && v == 1)) use_railways = false;
        u--; v--;
        em[u][v] = 1;
        em[v][u] = 1;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (em[i][j] == 0) em[i][j] = 2;
        }
    }
    auto edge_exists = [&](int u, int v, bool railways) -> bool {
        return (em[u][v] == 1 && railways) || (em[u][v] == 2 && !railways);
    };

    queue<int> q;
    q.push(0);
    dist[0] = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v = 0; v < n; v++) {
            if (edge_exists(u, v, use_railways) && dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
    cout << dist[n - 1] << '\n';

    return 0;
}
