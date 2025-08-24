#include <bits/stdc++.h>
using namespace std;

int64_t get_ans(int n, string s) {
    vector<int64_t> dpU(n + 1), dpB(n + 1);
    for (int i = 1; i <= n; i++) {
        if (s[i] == '0') {
            dpU[i] = dpU[i - 1] + i - 1;
            dpB[i] = dpB[i - 1] + (n - i);
        }
        else {
            assert(s[i] == '1');
            dpU[i] = dpB[i - 1] + 1;
            dpB[i] = 0;
        }
    }
    int64_t ans = 0;
    for (int i = 0; i <= n; i++) {
        ans = max({ans, dpU[i], dpB[i]});
    }
    return ans;
}

void solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    s.insert(s.begin(), '_');
    int64_t ans = get_ans(n, s);
    cout << ans << '\n';
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
