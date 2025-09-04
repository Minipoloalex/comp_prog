#include <bits/stdc++.h>
using namespace std;

void solve() {
    int R, C;
    cin >> R >> C;
    vector<vector<int>> g(R, vector<int>(C));
    for (auto &v: g) for (auto &val: v) cin >> val;

    vector<vector<int>> cnt(R, vector<int>(C));
    for (int i = 0; i < R; i++) {
        for (int j = C - 1; j >= 0; j--) {
            int valafter = j + 1 < C ? g[i][j + 1] : -1;
            int cntafter = j + 1 < C ? cnt[i][j + 1] : 0;
            if (g[i][j] == valafter) {
                cnt[i][j] = cntafter + 1;
            }
            else {
                cnt[i][j] = 1;
            }
        }
    }

    auto get_ans_col = [&](int j) {
        int64_t ans = 0;
        stack<pair<int,int>> s;
        int64_t cursum = 0;
        vector<int64_t> sums(R);
        for (int i = R - 1; i >= 0; i--) {
            int beforeval = i + 1 < R ? g[i + 1][j] : -1;
            int curval = g[i][j];
            int curcnt = cnt[i][j];

            int start = i;
            if (curval != beforeval) {
                // reset stuff
                cursum = 0;
                while (!s.empty()) s.pop();
            }

            while (!s.empty() && curcnt < s.top().second) {
                start = s.top().first;
                s.pop();
            }
            int dist = start - i + 1;

            // equivalent to what's below
            // if (start + 1 < R && g[start + 1][j] == curval) {
            //     cursum = sums[start + 1];
            // }
            // else {
            //     cursum = 0;
            // }
            cursum = s.empty() ? 0 : sums[start + 1];

            cursum += 1LL * curcnt * dist;
            sums[i] = cursum;
            ans += cursum;
            s.emplace(start, curcnt);
        }
        return ans;
    };
    int64_t ans = 0;
    for (int j = 0; j < C; j++) {
        ans += get_ans_col(j);
    }
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
