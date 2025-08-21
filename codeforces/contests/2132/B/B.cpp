#include <bits/stdc++.h>
using namespace std;

void solve() {
    int64_t n;
    cin >> n;
    vector<int64_t> ans;
    int64_t cur = 1;
    for (int i = 0; i < 18; i++) {
        cur *= 10;
        if (n % (cur + 1) == 0) {
            ans.push_back(n / (cur + 1));
        }
    }
    cout << ans.size() << '\n';
    if (ans.size()) {
        sort(ans.begin(), ans.end());
        for (int64_t v: ans) {
            cout << v << " ";
        }
        cout << '\n';
    }
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
