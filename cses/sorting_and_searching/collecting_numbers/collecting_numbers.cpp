#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> x(n);
    for (auto &xi: x) cin >> xi, xi--;
    vector<int> pos(n);
    for (int i = 0; i < n; i++) {
        pos[x[i]] = i;
    }
    int ans = 0;
    int curpos = n;
    for (int i = 0; i < n; i++) {
        if (pos[i] < curpos) {
            ans++;
        }
        curpos = pos[i];
    }
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
