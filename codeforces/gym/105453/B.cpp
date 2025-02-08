#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m; cin >> n >> m;
    vector<pair<int, int>> a(n);
    for (int i = 1; i <= n; i++) {
        auto& [f, s] = a[i-1];
        cin >> f;
        f = f / m + int(f % m != 0);
        s = i;
    }

    sort(a.begin(), a.end());

    for (auto& [_, i] : a) cout << i << ' ';
    cout << endl;
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    solve();
    return 0;
}
