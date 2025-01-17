#include <bits/stdc++.h>
using namespace std;

int n, steps;
vector<int> t, ans, vis;
queue<int> q;
void dfs(int u) {
    q.push(u);
    if (vis[u]) {
        steps += ans[u];
        return;
    }
    vis[u] = true;
    steps++;
    dfs(t[u]);
}

void solve() {
    cin >> n;
    t.resize(n);
    ans.assign(n, 0);
    vis.assign(n, 0);
    for (auto &x: t) {
        cin >> x;
        x--;
    }
    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            steps = 0;
            dfs(i);
            int dec = 1;
            while (!q.empty()) {
                int u = q.front();
                ans[u] = steps;
                if (q.front() == q.back()) {    // cycle
                    dec = 0;
                }
                steps -= dec;
                q.pop();
            }
        }
    }
    for (int i = 0; i < n; i++) cout << ans[i] << " \n"[i == n - 1];
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    solve();
    return 0;
}
