#include <bits/stdc++.h>
using namespace std;

struct Line {
    int64_t m, b;
    int64_t value(int64_t x) {
        return m * x + b;
    }
    // first X where line *this has a better (smaller y-value)
    int64_t first_better_x(const Line &other) const {
        assert(m < other.m);
        int64_t xceil = (b - other.b + (other.m - m - 1)) / (other.m - m);
        return xceil;
    }
};

void solve() {
    int n;
    int64_t c;
    cin >> n >> c;
    vector<int64_t> pos(n + 1);
    for (int i = 1; i <= n; i++) cin >> pos[i];

    vector<int64_t> dp(n + 1);

    vector<Line> lines;
    vector<int64_t> start;

    // monotone lines
    auto insert = [&](const Line &l) {
        while (!lines.empty() && lines.back().m == l.m) {
            if (lines.back().b <= l.b) {
                // existing is better: just avoid doing intersections with equal slopes
                return;
            }
            lines.pop_back();
            start.pop_back();
        }
        int64_t x = INT64_MIN;
        while (!lines.empty()) {
            x = l.first_better_x(lines.back());
            if (x <= start.back()) {
                lines.pop_back();
                start.pop_back();
            }
            else break;
        }
        lines.push_back(l);
        start.push_back(start.empty() ? INT64_MIN : x);
    };
    auto get_min = [&](int64_t posj) -> int64_t {
        int idx = int(upper_bound(start.begin(), start.end(), posj) - start.begin()) - 1;
        return lines[idx].value(posj);
    };
    for (int j = 1; j <= n; j++) {
        insert(Line{-2*pos[j], dp[j-1] + pos[j]*pos[j]});
        dp[j] = pos[j]*pos[j] + c + get_min(pos[j]);
    }
    cout << dp[n] << '\n';
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
