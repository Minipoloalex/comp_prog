#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    int ans = int(count(s.begin(), s.end(), '1'));
    
    if (s.find("111") != string::npos) {
        ans -= 2;
    }
    else if (s.find("11") != string::npos) {
        ans -= 1;
    }
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
