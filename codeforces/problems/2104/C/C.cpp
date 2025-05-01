#include <bits/stdc++.h>
using namespace std;

void solve() {
    size_t n;
    cin >> n;
    string s;
    cin >> s;
    string ans;
    if (s[0] == s[n - 1]) {
        ans = s[0] == 'A' ? "Alice" : "Bob";
    }
    else if (s[0] == 'A' && s[n - 1] == 'B') {
        size_t fb = s.find('B');
        if (fb != n - 1) ans = "Bob";
        else ans = "Alice";
    }
    else {
        size_t lstb = s.rfind('B');
        s.pop_back();
        size_t lsta = s.rfind('A');
        if (lsta == string::npos || lstb > lsta) {
            ans = "Bob";
        }
        else {
            ans = "Alice";
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
