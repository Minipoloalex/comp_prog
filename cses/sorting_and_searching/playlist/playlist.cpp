#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &ai: a) cin >> ai;
    set<int> s;
    int l = 0, r = 0;
    int ans = 0;
    while (r < n) {
        if (s.find(a[r]) != s.end()) {
            while (a[l] != a[r]) {
                s.erase(a[l++]);
            }
            s.erase(a[l++]);
        }
        s.insert(a[r++]);
        ans = max(ans, int(s.size()));
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
