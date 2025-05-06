#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a;
    int prev = -1;
    for (int i = 0; i < n; i++) {
        int ai;
        cin >> ai;
        if (ai == prev) {
            continue;
        }
        a.push_back(ai);
        prev = ai;
    }
    int ans = 0;
    n = int(a.size());
    for (int i = 0; i < n; i++) {
        bool is_max = true;
        if (i > 0) {
            is_max &= a[i] > a[i - 1];
        }
        if (i < n - 1) {
            is_max &= a[i] > a[i + 1];
        }
        if (is_max) ans++;
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
