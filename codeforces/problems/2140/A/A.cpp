#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    int cnt = (int)count(s.begin(), s.end(), '1');
    int ans = 0;
    for (int i = n - 1; i >= n - cnt; i--) {
        if (s[i] == '0') {
            ans++;
        }
    }
    cout << ans << '\n';
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
