#include <bits/stdc++.h>
using namespace std;

void solve() {
    vector<string> g(7);
    for (auto &s: g) cin >> s;
    int d, h;
    cin >> d >> h;

    vector<int> days(7);
    for (int i = 0; i < d; i++) {
        days[i] = 1;
    }
    int mx_count = 0;
    sort(days.begin(), days.end());
    do {
        vector<int> hours(24);
        for (int i = 0; i < 7; i++) {
            if (days[i] == 0) {
                continue;
            }
            for (int j = 0; j < 24; j++) {
                if (g[i][j] == '.') hours[j]++;
            }
        }
        sort(hours.rbegin(), hours.rend());
        int cnt = 0;
        for (int i = 0; i < h; i++) {
            cnt += hours[i];
        }
        mx_count = max(mx_count, cnt);
    } while (next_permutation(days.begin(), days.end()));
    double ans = double(mx_count) / (h * d);
    cout << fixed << setprecision(10) << ans << '\n';
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
