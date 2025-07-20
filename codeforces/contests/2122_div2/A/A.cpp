#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;
    bool ans;
    if ((n <= 2 && m <= 2) || n == 1 || m == 1) {
        ans = false;
    }
    else ans = true;
    cout << (ans ? "YES" : "NO") << '\n';
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
