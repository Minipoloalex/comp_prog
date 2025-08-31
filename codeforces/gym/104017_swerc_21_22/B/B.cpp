#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int,int> ii;

typedef vector<ii> vii;
typedef vector<vii> vvii;

void solve() {
    int n;
    cin >> n;
    vvi a(n, vi(n));
    for (auto &v: a) for (auto &val: v) cin >> val;
    vvi row(n, vi(n)), col(n, vi(n));
    for (int i = 0; i < n; i++) {
        vi v(n);
        iota(v.begin(), v.end(), 0);
        sort(v.begin(), v.end(), [&](int l, int r) {
            return a[i][l] < a[i][r];
        });
        for (int j = 0; j < n; j++) {
            int origidx = v[j];
            row[i][origidx] = j;
        }
    }
    for (int j = 0; j < n; j++) {
        vi v(n);
        iota(v.begin(), v.end(), 0);
        sort(v.begin(), v.end(), [&](int l, int r) {
            return a[l][j] < a[r][j];
        });
        for (int i = 0; i < n; i++) {
            int origidx = v[i];
            col[origidx][j] = i;
        }
    }
    int64_t ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int smaller_row = row[i][j];
            // int greater_row = n - 1 - row[i][j];
            // int smaller_col = col[i][j];
            int greater_col = n - 1 - col[i][j];
            ans += 1LL * smaller_row * greater_col;
            // ans += 1LL * greater_row * smaller_col;
        }
    }
    // cout << ans / 2 << '\n'; // overcounting, then dividing by 2 may be easier to understand
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
