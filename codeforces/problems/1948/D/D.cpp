#include <bits/stdc++.h>
using namespace std;

void solve() {
    string s;
    cin >> s;
    int n = int(s.size());
    int ans = 0;
    auto equal = [](char a, char b) {
        return a == b || a == '?' || b == '?';
    };
    for (int sz = 1; sz <= n / 2; sz++) {
        int checks = 0;
        string s1 = s.substr(0, sz);
        string s2 = s.substr(sz, sz);
        assert(int(s1.size()) == sz && int(s2.size()) == sz);
        for (int i = 0; i < sz; i++) {
            if (equal(s1[i], s2[i])) checks++;
        }
        if (checks == sz) ans = max(ans, sz);
        for (int i = 1; i + 2 * sz - 1 < n; i++) {
            if (equal(s[i - 1], s[i - 1 + sz])) checks--;
            if (equal(s[i + sz - 1], s[i + 2*sz - 1])) checks++;
            if (checks == sz) {
                ans = max(ans, sz);
            }
        }
    }
    cout << ans * 2 << '\n';
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
