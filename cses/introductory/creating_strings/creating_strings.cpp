#include <bits/stdc++.h>
using namespace std;

void solve() {
    string s;
    cin >> s;
    sort(s.begin(), s.end());
    vector<string> ans;
    do {
        ans.push_back(s);
    } while (next_permutation(s.begin(), s.end()));
    cout << ans.size() << '\n';
    for (auto &st: ans) {
        cout << st << '\n';
    }
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
