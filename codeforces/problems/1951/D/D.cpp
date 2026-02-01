#include <bits/stdc++.h>
using namespace std;

void solve() {
    int64_t n, k;
    cin >> n >> k;
    if (k == n) {
        cout << "YES\n";
        cout << "1\n1\n";
    }
    else if (k > (n+1)/2) {
        cout << "NO\n";
    }
    else {
        vector<int64_t> ans;
        ans.push_back(n-k+1);
        ans.push_back(1);
        cout << "YES\n";
        cout << ans.size() << '\n';
        for (int64_t val: ans) cout << val << " ";
        cout << '\n';
    }
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
