#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    map<int, int> f;

    int mx = 0;
    for (int i = 0; i < n; i++) {
        int x; cin >> x; f[x]++;
        mx = max(x, mx);
    }

    if (n == 1) {
        cout << "N" << '\n';
        return;
    }

    int cnt = 0;
    for (int i = 0; i <= mx + 10000; i++) {
        if (f[i] & 1) cnt++;
        f[i+1] += f[i] / 2;
    }

    cout << (cnt <= 2 ? "Y" : "N") << '\n';
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
