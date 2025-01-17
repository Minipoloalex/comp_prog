#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> suc(n);
    for (int i = 0; i < n; i++) {
        int pi;
        cin >> pi;
        pi--;
        suc[i] = pi;
    }
    vector<int> vis;
    for (int i = 0; i < n; i++) {
        vis.assign(n, 0);
        int nd = i;
        while (!vis[nd]) {
            vis[nd] = 1;
            nd = suc[nd];
        }
        cout << nd + 1 << " ";
    }
    cout << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    solve();
    return 0;
}
