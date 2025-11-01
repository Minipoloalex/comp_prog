#include <bits/stdc++.h>
using namespace std;

void solve() {
    using p = array<int, 2>;
    int n, m; cin >> n >> m;
    vector<p> a(m);

    for (int i = 0; i < m; i++) {
        int l, r; cin >> l >> r;
        a[i][0] = l - 1;
        a[i][1] = r - 1;
    }

    for (auto& [l, r] : a) {
        int len = r - l + 1;
        if (len & 1) {
            cout << "N\n";
            return;
        }
    }
    cout << "Y\n";
    for (int i = 0; i < n; i++) {
        cout << "MT"[i % 2];
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
