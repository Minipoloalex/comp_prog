#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;  // k < n
    string s;
    cin >> s;
    int cnt = (int)count(s.begin(), s.end(), '1');
    bool ans;
    if (cnt <= k || n < 2*k) {
        ans = true;
    }
    else ans = false;
    cout << (ans ? "Alice" : "Bob") << '\n';
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
