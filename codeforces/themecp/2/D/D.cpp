#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &x: a) cin >> x;
    vector<int> vis(n, 0);
    int cur = 0;
    for (int b = 0; b < 31; b++) {
        int mx = 0;
        int idx = -1;
        for (int i = 0; i < n; i++) {
            int ival = cur | a[i];
            if (!vis[i] && ival > mx) {
                mx = ival;
                idx = i;
            }
        }
        if (idx != -1) {
            vis[idx] = 1;
            cur = mx;
            cout << a[idx] << " ";
        }
    }
    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            cout << a[i] << " ";
        }
    }
    cout << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
