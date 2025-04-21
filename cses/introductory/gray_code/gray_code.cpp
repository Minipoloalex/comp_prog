#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<string> ans;

    string cur(n, '0');
    function<void(int)> handle = [&](int i) {
        if (i == n) {
            ans.push_back(cur);
            return;
        }
        handle(i + 1);

        int ci = cur[i] - '0';
        int nci = ci ^ 1;
        cur[i] = char('0' + nci);
        handle(i + 1);
    };

    handle(0);
    for (auto &s: ans) {
        cout << s << '\n';
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
