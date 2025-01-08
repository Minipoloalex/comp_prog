#include <bits/stdc++.h>
using namespace std;

#define ALL string("urdl")
void solve() {
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    int n;
    cin >> n;
    string s;
    cin >> s;
    map<char, vector<int>> map;
    for (char c: ALL) map[c].assign(n, 0);
    for (int i = 0; i < n; i++) {
        char c = char(tolower(s[i]));
        if (i > 0) {
            for (char ch: ALL) {
                map[ch][i] += map[ch][i - 1];
            }
        }
        map[c][i]++;
    }
    auto possible = [&](int64_t iters) -> bool {
        int64_t loops = iters / n;
        int64_t rst = iters % n - 1;

        int64_t yd = (map['u'].back() - map['d'].back()) * loops;
        int64_t xd = (map['r'].back() - map['l'].back()) * loops;
        if (rst != -1) {
            // If it was 1-indexed, this would not be necessary (definitely better to use 1-index here)
            yd += map['u'][rst] - map['d'][rst];
            xd += map['r'][rst] - map['l'][rst];
        }

        int64_t xleft = abs(x2 - (x1 + xd));
        int64_t yleft = abs(y2 - (y1 + yd));
        return iters >= xleft + yleft;
    };

    const int64_t MAX = int64_t(1e14 + 1);  // 1e9 * 1e5 can be a solution
    // Safe solution: 1e18
    // 1e14 fails, 1e14 + 1 is enough
    int64_t lo = 0, hi = int64_t(MAX);
    while (lo < hi) {
        int64_t m = lo + (hi - lo) / 2;
        if (possible(m)) {
            hi = m;
        }
        else {
            lo = m + 1;
        }
    }
    if (lo == MAX) lo = -1;
    cout << lo << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    solve();
    return 0;
}
