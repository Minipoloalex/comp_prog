#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    vector<int> mx(11, -1);

    for (int i = 0; i < n; i++) {
        int x, b;
        cin >> b >> x;
        mx[x] = max(mx[x], b);
    }

    int ans = 0;
    for (int i = 1; i < 11; i++) {
        ans += mx[i];
        if (mx[i] == -1) {
            cout << "MOREPROBLEMS\n";
            return;
        }
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
