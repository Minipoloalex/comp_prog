#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &x: a) cin >> x;
    int mn = *min_element(a.begin(), a.end());
    int cnt = int(count(a.begin(), a.end(), mn));
    string ans = "NO";
    if (cnt == 1) {
        ans = "YES";
    }
    else {
        // cnt > 1
        for (int i = 0; i < n; i++) {
            if (a[i] % mn != 0) ans = "YES";
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
