#include <bits/stdc++.h>
using namespace std;

void solve() {
    string s;
    cin >> s;
    int mn = INT_MAX;
    int n = int(s.size());
    for (int i = 0; i < n; i++) {
        mn = min(mn, s[i] - '0');
    }
    cout << mn << '\n';
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
