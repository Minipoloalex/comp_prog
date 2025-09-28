#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> x(n);
    vector<char> ops(n - 1);
    cin >> x[0];
    for (int i = 1; i < n; i++) {
        cin >> ops[i-1];
        cin >> x[i];
    }
    vector<int> mp(n);
    vector<pair<int,int>> parts;
    for (int i = 0; i < n; ) {
        int cur = i;
        while (cur < n - 1 && ops[cur] == '*') {
            cur++;
        }
        pair<int,int> cnts{};
        for (int j = i; j <= cur; j++) {
            mp[j] = int(parts.size());
            if (x[j] % 2 == 0) {
                cnts.first++;
            }
            else {
                cnts.second++;
            }
        }
        parts.push_back(cnts);
        i = cur + 1;
    }
    int cnt_odds = 0;
    for (auto &[evens, odds]: parts) {
        if (evens == 0) cnt_odds++;
    }

    {
        bool even = cnt_odds % 2 == 0;
        cout << (even ? "even" : "odd") << '\n';
    }
    while (m--) {
        int i, y;
        cin >> i >> y;
        i--;

        int part_idx = mp[i];
        if (x[i] % 2 != y % 2) {
            auto &[evens, odds] = parts[part_idx];
            int before_evens = evens;
            if (x[i] % 2 == 0) {
                odds++;
                evens--;
            }
            else {
                odds--;
                evens++;
            }
            if (before_evens == 0 && evens > 0) {
                cnt_odds--;
            }
            if (before_evens > 0 && evens == 0) {
                cnt_odds++;
            }
        }
        x[i] = y;
        bool even = cnt_odds % 2 == 0;
        cout << (even ? "even" : "odd") << '\n';
    }
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
