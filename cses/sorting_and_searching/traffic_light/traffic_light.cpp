#include <bits/stdc++.h>
using namespace std;

void solve() {
    int x, n;
    cin >> x >> n;
    set<int> s = {0, x};
    multiset<int> distances = {x};
    for (int i = 0; i < n; i++) {
        int p;
        cin >> p;

        auto it = s.upper_bound(p);
        int r = *it;
        int l = *--it;
        distances.erase(distances.find(r - l));
        distances.insert(r - p);
        distances.insert(p - l);
        s.insert(p);

        int ans = *(--distances.end());
        cout << ans << " ";
    }
    cout << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    solve();
    return 0;
}
