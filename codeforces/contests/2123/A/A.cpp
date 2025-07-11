#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    string ans;
    if (n % 4 != 0) {
        ans = "Alice";
    }
    else ans = "Bob";
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
