#include <bits/stdc++.h>
using namespace std;

void solve() {
    string s, t;
    cin >> s >> t;
    vector<int> sc(26, INT_MAX), st(26, -1);
    for (int i = 1; i < int(s.size()); i++) {
        int c = s[i] - 'a';
        sc[c] = min(sc[c], i);
    }
    for (int i = int(t.size() - 2); i >= 0; i--) {
        int c = t[i] - 'a';
        st[c] = max(st[c], i);
    }
    int ts = int(t.size());
    pair<int,int> ans = {-1, -1};
    auto get_best = [&](pair<int,int> cur) {
        if (ans == make_pair(-1,-1)) {
            ans = cur;
            return;
        }
        int total = cur.first + (ts - cur.second);
        int anstotal = ans.first + (ts - ans.second);
        if (total < anstotal) {
            ans = cur;
        }
    };
    for (int i = 0; i < 26; i++) {
        if (sc[i] == INT_MAX || st[i] == -1) continue;
        get_best(make_pair(sc[i], st[i]));
    }
    if (ans == make_pair(-1, -1)) {
        cout << "-1\n";
    }
    else {
        cout << s.substr(0, ans.first + 1) + t.substr(ans.second + 1) << endl;
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
