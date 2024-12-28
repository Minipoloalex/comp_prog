#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &x: a) cin >> x;

    multiset<int> s;
    s.insert(max(a[0], a[1]));
    for (int i = 2; i < n; i += 2) {
        int mn = min(a[i], a[i + 1]);
        int mx = max(a[i], a[i + 1]);
        s.insert(mx);
        int smin = *s.begin();
        if (mn > smin) {
            s.erase(s.begin());
            s.insert(mn);
        }
    }
    int64_t ans = 0;
    for (int value: s) ans += value;
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    solve();
    return 0;
}
