#include <bits/stdc++.h>
using namespace std;

void solve() {
    string s; cin >> s;
    cout << (s <= "2023-09-16" ? "GOOD" : "TOO LATE") << '\n';
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
