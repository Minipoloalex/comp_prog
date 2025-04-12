#include <bits/stdc++.h>
using namespace std;

void solve() {
    int k;
    cin >> k;
    cout << ((k % 2 == 0) ? "NO" : "YES") << '\n';
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
