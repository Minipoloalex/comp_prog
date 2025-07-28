#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    array<string, 2> h;
    cin >> h[0] >> h[1];
    auto score = [](char a, char b, char c) {
        string s;
        s += a;
        s += b;
        s += c;
        sort(s.begin(), s.end());
        return s[0] == 'A' && s[1] == 'A' ? 1 : 0;
    };
    auto line_score = [&](int i, int c) {
        return score(h[c][i], h[c][i + 1], h[c][i + 2]);
    };
    auto r_score = [&](int i) {
        return score(h[0][i], h[1][i], h[0][i + 1]);
    };
    auto L_score = [&](int i) {
        return score(h[0][i], h[1][i], h[1][i + 1]);
    };
    auto score_7 = [&](int i) {
        return score(h[0][i], h[0][i + 1], h[1][i + 1]);
    };
    auto score_J = [&](int i) {
        return score(h[1][i], h[0][i + 1], h[1][i + 1]);
    };

    vector<vector<int>> dp(n, vector<int>(4, -1));
    function<int(int,int)> go = [&](int i, int covered) {
        if (i == n) return 0;

        int &ans = dp[i][covered];
        if (ans != -1) return ans;
        int mx;
        if (covered == 0) {
            int L = go(i + 1, 1) + L_score(i);
            int r = go(i + 1, 2) + r_score(i);
            int two_lines = go(i + 3, 0) + line_score(i, 0) + line_score(i, 1);
            mx = max(max(L, r), two_lines);
        }
        else if (covered == 1) {
            // previously had a shape like an L
            mx = go(i + 2, 0) + score_7(i);
            if (i < n - 2) {
                mx = max(mx, go(i + 3, 1) + line_score(i, 0) + line_score(i + 1, 1));
            }
        }
        else if (covered == 2) {
            // previously had a shape like a gamma (or an r)
            mx = go(i + 2, 0) + score_J(i);
            if (i < n - 2) {
                mx = max(mx, go(i + 3, 2) + line_score(i, 1) + line_score(i + 1, 0));
            }
        }
        return ans = mx;
    };
    int ans = go(0, 0);
    cout << ans << '\n';
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
