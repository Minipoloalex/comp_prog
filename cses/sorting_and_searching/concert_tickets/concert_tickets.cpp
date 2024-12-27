#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;
    multiset<int> h;
    for (int i = 0; i < n; i++) {
        int hi;
        cin >> hi;
        h.insert(hi);
    }
    while (m--) {
        int p;
        cin >> p;
        auto it = h.upper_bound(p);
        int ans = -1;
        if (it != h.begin()) {
            ans = *--it;
            h.erase(it);   // remove one occurrence only
        }
        cout << ans << '\n';
    }
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    solve();
    return 0;
}
