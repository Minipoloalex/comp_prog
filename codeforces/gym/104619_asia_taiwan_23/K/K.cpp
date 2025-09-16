#include <bits/stdc++.h>
using namespace std;

void solve() {
    string s;
    cin >> s;
    int n = int(s.size());
    int cnt = 0;
    string check = "kick";
    for (int i = 0; i < n; i++) {
        if (s.substr(i, 4) == check) cnt++;
    }
    cout << cnt << '\n';
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
