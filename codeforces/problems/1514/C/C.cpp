#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    int64_t prod = 1;
    vector<int> ans;
    for (int i = 1; i < n; i++) {
        if (gcd(i, n) == 1) {
            ans.push_back(i);
            (prod *= i) %= n;
        }
    }
    cout << ans.size() - (prod != 1) << '\n';
    for (int a: ans) {
        if (prod == 1 || a != prod) {
            cout << a << " ";
        }
    }
    cout << '\n';
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
