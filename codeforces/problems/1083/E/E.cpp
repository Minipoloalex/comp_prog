#include <bits/stdc++.h>
using namespace std;

struct Line {
    int64_t m, b;
    int64_t value(int64_t x) {
        return m * x + b;
    }
    // last X where line *this has a better (larger y-value)
    int64_t last_better_x(const Line &other) const {
        assert(m < other.m);
        int64_t xfloor = (b - other.b) / (other.m - m);
        return xfloor;
    }
};
deque<Line> lines;
deque<int64_t> last;

// monotone lines
void insert(const Line &l) {
    while (!lines.empty() && lines.front().m == l.m) {
        if (lines.front().b >= l.b) {
            // existing is better: just avoid doing intersections with equal slopes
            // for this problem, it doesn't matter since there are no equal slopes
            return;
        }
        lines.pop_front();
        last.pop_front();
    }
    int64_t x = INT64_MAX;
    while (!lines.empty()) {
        x = l.last_better_x(lines.front());
        if (x >= last.front()) {
            lines.pop_front();
            last.pop_front();
        }
        else break;
    }
    lines.push_front(l);
    last.push_front(last.empty() ? INT64_MAX : x);
}
int64_t get_max(int64_t x) {
    int idx = int(lower_bound(last.begin(), last.end(), x) - last.begin());
    return lines[idx].value(x);
}

void solve() {
    int n;
    cin >> n;
    vector<array<int64_t,3>> rects(n);
    for (auto &[x, y, a]: rects) cin >> x >> y >> a;
    sort(rects.begin(), rects.end());
    vector<int64_t> dp(n);
    insert(Line{0, 0});
    for (int i = 0; i < n; i++) {
        auto &[x, y, a] = rects[i];
        int64_t mx_sum = get_max(y);
        dp[i] = mx_sum - a + x * y;
        insert(Line{-x, dp[i]});
    }
    int64_t ans = *max_element(dp.begin(), dp.end());
    cout << ans << '\n';
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
