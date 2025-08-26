#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, a, b;
    cin >> n >> a >> b;
    int mx = max(a, b);
    bool ans;
    if (n % 2 == 0) {
        ans = mx % 2 == 0 && b % 2 == 0;
    }
    else {
        ans = mx % 2 == 1 && b % 2 == 1;
    }
    cout << (ans ? "YES": "NO") << '\n';
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
