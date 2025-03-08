#include <bits/stdc++.h>
using namespace std;

void solve() {
    string s, t;
    cin >> s >> t;
    int cnt = (int) count(t.begin(), t.end(), 'a');
    int64_t ans;
    if (t == "a") {
        ans = 1;
    }
    else if (cnt > 0 && int(t.size()) > 1) {
        ans = -1;
    }
    else {
        ans = 1LL << s.size();
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
