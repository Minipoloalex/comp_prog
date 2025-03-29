#include <bits/stdc++.h>
using namespace std;

void solve() {
    int k;
    cin >> k;
    int v1 = 0, v2 = 0, v3 = 0;
    vector<int> d(k);
    vector<int> ans;
    for (int i = 0; i < k; i++) {
        int di;
        cin >> di;
        d[i] = di;
        if (di == 0) {
            ans.push_back(0);
        }
        else if (di == 100) {
            ans.push_back(100);
        }
        else if (di < 10) {
            v1 = di;
        }
        else {  // di >= 10
            v2 = di;
            if (di % 10 == 0) v3 = di;
        }
    }
    if (v1 > 0) {
        ans.push_back(v1);
        if (v3 > 0) ans.push_back(v3);
    }
    else {
        if (v2 > 0) ans.push_back(v2);
    }
    cout << ans.size() << '\n';
    for (int a: ans) cout << a << " ";
    cout << '\n';
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
