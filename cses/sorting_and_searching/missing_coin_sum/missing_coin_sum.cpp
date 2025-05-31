#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> x(n);
    for (auto &xi: x) cin >> xi;
    sort(x.begin(), x.end());
    int64_t sm = 0;
    for (auto xi: x) {
        if (xi <= sm + 1) {
            sm += xi;
        }
        else break;
    }
    cout << sm + 1 << '\n';
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
