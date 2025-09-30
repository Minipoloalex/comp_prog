#include <bits/stdc++.h>
using namespace std;

void solve() {
    vector<int> cnt(5);
    for (int i = 0; i < 10; i++) {
        int di;
        cin >> di;
        cnt[di]++;
    }
    int ans = 0;
    for (int i = 1; i <= 4; i++) {
        ans += (cnt[i] == 0);
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
