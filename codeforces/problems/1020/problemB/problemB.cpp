#include <bits/stdc++.h>
using namespace std;

vector<int> suc;
vector<int> vis;
bool inside_cycle = false;

void dfs(int u) {
    if (vis[u] != -2) { // already processed
        if (vis[u] == -1) {
            inside_cycle = true;
            vis[u] = u;
        }
        return;
    }
    vis[u] = -1;
    dfs(suc[u]);
    if (vis[u] == u) {  // visited from the cycle and set to self (same as vis[u] != -1)
        inside_cycle = false;
    }
    else {
        vis[u] = inside_cycle ? u : vis[suc[u]];
    }
}

void solve() {
    int n;
    cin >> n;
    suc.resize(n);
    for (int i = 0; i < n; i++) {
        int pi;
        cin >> pi;
        pi--;
        suc[i] = pi;
    }
    vis.assign(n, -2);
    for (int i = 0; i < n; i++) {
        dfs(i);
        cout << vis[i] + 1 << " ";
    }
    cout << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    solve();
    return 0;
}
