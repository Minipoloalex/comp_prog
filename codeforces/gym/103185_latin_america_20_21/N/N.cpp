#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    auto read = [&]() {
        char c;
        cin >> c;
        double nr;
        cin >> nr;
        return (int)round(nr * 100);
    };
    int cur = read();
    int ans = 0;
    for (int i = 0; i < n; i++) {
        int v = read();
        cur += v;
        if (cur % 100 != 0) {
            ans++;
        }
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
