#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    vector<int> a(n + 2);
    a[0] = 0;
    a[n+1] = 1440;

    for (int i = 1; i <= n; i++) cin >> a[i];

    bool good = false;
    int cnt = 0;
    for (int i = 1; i <= n + 1; i++) {
        int df = a[i] - a[i-1];
        if (df >= 240) good = true;
        if (df >= 120) cnt++;
    }

    cout << ((cnt >= 2 || good) ? "YES" : "NO") << '\n';
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
