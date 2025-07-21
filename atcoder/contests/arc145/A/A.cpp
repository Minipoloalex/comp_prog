#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    bool ans;
    if (n == 1) {
        ans = true;
    }
    else if (n == 2) {
        ans = s[0] == s[n - 1];
    }
    else if (s[0] == 'A' && s[n-1] == 'B') {
        ans = false;
    }
    else if (s[0] == 'A' && s[n-1] == 'A') {
        ans = true;
    }
    else if (s[0] == 'B' && s[n-1] == 'A') {
        ans = true;
    }
    else {  //  if (s[0] == 'B' && s[n-1] == 'B')
        ans = true;
    }

    cout << (ans ? "Yes" : "No") << '\n';
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
