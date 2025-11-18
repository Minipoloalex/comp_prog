#include <bits/stdc++.h>
using namespace std;

void finish(bool ans) {
    cout << (ans ? "Monocarp" : "Polycarp") << '\n';
}

map<char,int> mp = {
    {'(', 1},
    {')', -1},
};

void solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    vector<vector<int>> dp(n, vector<int>(n,-1));
    function<int(int,int,bool)> go = [&](int l, int r, bool who) {
        if (l > r) {
            return 0;
        }
        int &mem = dp[l][r];
        if (mem != -1) return mem;

        int cur;
        if (who) {
            cur = min(0, max(go(l+1,r,!who), go(l,r-1,!who)));
        }
        else {
            bool start = l == 0 && r == n-1;
            if (start) {
                if (s.front() == ')' && s.back() == '(') {
                    cur = mp[s[r]] + go(l,r-1,!who);
                }
                else if (s.front() == ')' && s.back() == ')') {
                    cur = INT_MAX;
                }
                else if (s.front() == '(' && s.back() == ')') {
                    cur = mp[s[l]] + go(l+1,r,!who);
                }
                else {
                    assert(s.front() == '(' && s.back() == '(');
                    cur = min(mp[s[l]] + go(l+1,r,!who), mp[s[r]] + go(l,r-1,!who));
                }
            }
            else {
                cur = min(mp[s[l]] + go(l+1,r,!who), mp[s[r]] + go(l,r-1,!who));
            }
        }
        return mem = cur;
    };
    int ans = go(0, n-1, 0);
    finish(ans <= 0);
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
