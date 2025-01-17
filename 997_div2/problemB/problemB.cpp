#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<string> g(n);
    for (int i = 0; i < n; i++) {
        cin >> g[i];
    }
    vector<int> ans{0};
    for (int i = 1; i < n; i++) {
        bool inserted = false;
        for (int j = 0; j < int(ans.size()); j++) {
            int jval = ans[j];
            if (g[jval][i] == '0') {
                ans.insert(ans.begin() + j, i);
                inserted = true;
                break;
            }
        }
        if (!inserted) ans.push_back(i);
    }
    for (int v: ans) cout << v + 1 << " ";
    cout << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
