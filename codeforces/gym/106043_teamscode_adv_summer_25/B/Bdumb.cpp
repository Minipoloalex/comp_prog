#include <bits/stdc++.h>
using namespace std;

int64_t get(int64_t n, int64_t height, int64_t last_height) {
    if (n == 0) return 0;
    if (n < 0) return INT64_MIN;
    int64_t levels_to_cover = last_height - height + 1;
    int64_t i;
    for (i = 0; ; i++) {
        int64_t nr_levels = i + 1;
        int64_t missing_levels = levels_to_cover - nr_levels;
        if (missing_levels < 0) {
            break;
        }
        int64_t wasted_nr = (1LL << (i + 1)) - 1 + missing_levels;
        if (n < wasted_nr) break;
    }
    int64_t last_possible = i - 1;
    if (last_possible == -1) return 0;

    int64_t nr_levels = last_possible + 1;
    int64_t missing_levels = levels_to_cover - nr_levels;
    int64_t wasted_nr = (1LL << (last_possible + 1)) - 1 + missing_levels;
    return (1LL << last_possible) + get(n - wasted_nr, last_height - last_possible, last_height);
}

void solve() {
    // log N but quite stupid
    int64_t n;
    cin >> n;
    int64_t full = int64_t(log2(n + 1));
    int64_t last_complete_nr = 1LL << (full - 1);

    int64_t ans = last_complete_nr;
    int64_t rem = n - (1LL << full);
    if (rem > 0) {
        int64_t other = get(rem, 1, full);
        ans = max(ans, last_complete_nr + other);
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
