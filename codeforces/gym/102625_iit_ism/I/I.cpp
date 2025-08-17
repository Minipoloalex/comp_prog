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
    vector<int64_t> s(n + 1);
    for (int i = 1; i <= n; i++) cin >> s[i];
    vector<int64_t> prefsum(n + 1), prefsumiota(n + 1);
    for (int i = 1; i <= n; i++) {
        prefsum[i] = prefsum[i - 1] + s[i];
    }
    for (int i = 1; i <= n; i++) {
        prefsumiota[i] = prefsumiota[i - 1] + i * s[i];
    }
    /*
    Formula: dp[j] = prefsumiota[j] - prefsumiota[i] - i * (prefsum[j] - prefsum[i])
    Doesn't depend on i: prefsumiota[j]
    Depends only on i (intercept): i*prefsum[i] - prefsumiota[i]
    Depends on j (slope): -i*prefsum[j]
    Instead of passing j as the X, we pass prefsum[j]
    */
    vector<int64_t> dp(n + 1);
    insert(Line{0,0});
    for (int i = 1; i <= n; i++) {
        insert(Line{-i, i*prefsum[i] - prefsumiota[i]});
        int64_t mx = get_max(prefsum[i]);
        dp[i] = prefsumiota[i] + mx;
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
