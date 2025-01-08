#include <bits/stdc++.h>
using namespace std;

void solve() {
    freopen("haybales.in", "r", stdin);
    freopen("haybales.out", "w", stdout);
    int n, q;
    cin >> n >> q;
    vector<int> hay(n);
    for (auto &x: hay) cin >> x;
    sort(hay.begin(), hay.end());
    while (q--) {
        int a, b;
        cin >> a >> b;
        cout << upper_bound(hay.begin(), hay.end(), b) - lower_bound(hay.begin(), hay.end(), a) << '\n';
    }
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    solve();
    return 0;
}
