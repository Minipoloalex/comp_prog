#include <bits/stdc++.h>
using namespace std;

int64_t solve_ch(int n, string s, char c) {
    int total = int(count(s.begin(), s.end(), c));
    int cur = 0;
    int64_t ans = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == c) {
            cur++;
        }
        else {
            int rem = total - cur;
            int use = min(rem, cur);
            ans += use;
        }
    }
    return ans;
}

void solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    int64_t ans = min(solve_ch(n, s, 'a'), solve_ch(n, s, 'b'));
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
