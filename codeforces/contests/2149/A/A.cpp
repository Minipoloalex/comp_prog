#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    int ans = 0;
    int cnt = 0;
    for (auto &ai: a) {
        cin >> ai;
        if (ai == 0) {
            ans++;
        }
        else if (ai == -1) {
            cnt++;
        }
    }
    if (cnt % 2 == 1) {
        ans += 2;
    }
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
