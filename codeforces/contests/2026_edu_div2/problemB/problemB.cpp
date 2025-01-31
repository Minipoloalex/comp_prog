#include <bits/stdc++.h>
using namespace std;

int64_t solve_odd(vector<int64_t> &a, int n) {
    int64_t ans = INT64_MAX;
    for (int i = 0; i < n; i++) {
        int64_t prev = -1, ansi = 1;
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            if (prev == -1) {
                prev = a[j];
            }
            else {
                ansi = max(ansi, a[j] - prev);
                prev = -1;
            }
        }
        // cout << i << " " << ansi << '\n';
        ans = min(ans, ansi);
    }
    return ans;
}
int64_t solve_even(vector<int64_t> &a, int n) {
    int64_t ans = 1;
    for (int i = 0; i < n; i += 2) {
        ans = max(ans, a[i + 1] - a[i]);
    }
    return ans;
}


int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int64_t> a(n);
        for (auto &ai: a) cin >> ai;
        int64_t ans;
        if ((n & 1) == 1) {
            ans = solve_odd(a, n);
        }
        else {
            ans = solve_even(a, n);
        }
        cout << ans << '\n';
    }
    return 0;
}
