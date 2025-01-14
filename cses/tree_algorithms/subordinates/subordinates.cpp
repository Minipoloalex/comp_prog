#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> g;
vector<int> cs;
int n;

void dfs(int u, int p) {
    int ans = 0;
    for (int v: g[u]) {
        if (v != p) {
            dfs(v, u);
            ans += 1 + cs[v];
        }
    }
    cs[u] = ans;
}

void solve() {
    cin >> n;
    cs.assign(n, 0);
    g.assign(n, vector<int>());
    for (int i = 1; i < n; i++) {
        int pi;
        cin >> pi;
        pi--;
        g[i].push_back(pi);
        g[pi].push_back(i);
    }
    dfs(0, -1);
    for (int i = 0; i < n; i++) {
        cout << cs[i] << " ";
    }
    cout << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    solve();
    return 0;
}
