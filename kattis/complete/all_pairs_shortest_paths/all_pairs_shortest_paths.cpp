#include <bits/stdc++.h>
using namespace std;

#define INF 1e8

int AM[150][150];

int main() {
    while (true) {
        int n, m, q;
        cin >> n >> m >> q;
        if (n == 0 && m == 0 && q == 0) break;

        memset(AM, 63, sizeof AM);
        for (int i = 0; i < n; i++) {
            AM[i][i] = 0;
        }
        for (int i = 0; i < m; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            // u could be equal to v (and we could get + or - self loop)
            AM[u][v] = min(w, AM[u][v]);
        }

        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (AM[i][k] < INF && AM[k][j] < INF && AM[i][k] + AM[k][j] < AM[i][j]) {
                        AM[i][j] = AM[i][k] + AM[k][j];
                    }
                }
            }
        }
        // how to detect negative loops with floyd-warshall
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < n; k++) {
                    if (AM[k][k] < 0 && AM[i][k] < INF && AM[k][j] < INF) {
                        AM[i][j] = -INF;
                        break;
                    }
                }
            }
        }
        for (int i = 0; i < q; i++) {
            int u, v;
            cin >> u >> v;
            int res = AM[u][v];
            if (res == -INF) cout << "-Infinity" << endl;
            else if (res >= INF) cout << "Impossible" << endl;
            else cout << res << endl;
        }
        cout << endl;
    }
    return 0;
}

