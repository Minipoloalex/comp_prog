#include <bits/stdc++.h>
using namespace std;

const int MAX = int(1e5);

void solve() {
    int a, b;
    cin >> a >> b;
    int ans = INT_MAX;
    for (int i = 1; i <= MAX; i++) {
        int cur = (i - 1) + (a + i - 1) / i + (b + i - 1) / i;
        ans = min(ans, cur);
    }
    cout << ans << '\n';
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
