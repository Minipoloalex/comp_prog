#include <bits/stdc++.h>
using namespace std;

const int64_t MOD = 998244353;

const int MAX_N = int(2e5);
int64_t dp[MAX_N + 1][4];


int n;
vector<int> a;
int64_t go(int i, int s) {
    if (s == 3) return 1;
    if (i == n) return 0;

    int64_t &ans = dp[i][s];
    if (ans != -1) return ans;

    int64_t cur = go(i + 1, s);
    if (a[i] == 3 && s == 2) (cur += go(i + 1, 3)) %= MOD;
    else if (a[i] == 2 && (s == 1 || s == 2)) (cur += go(i + 1, 2)) %= MOD;
    else if (a[i] == 1 && s == 0) (cur += go(i + 1, 1)) %= MOD;
    return ans = cur;
}

void solve_dp() {
    cin >> n;
    a.resize(n);
    for (auto &x: a) cin >> x;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 4; j++) {
            dp[i][j] = -1;
        }
    }
    int64_t ans = go(0, 0);
    cout << ans << '\n';
}

// void solve() {
//     int n;
//     cin >> n;
//     vector<int> a(n);
//     for (auto &x: a) cin >> x;
//     int64_t cur_cnt = 0, total_cnt = 0, total = 0;
//     int64_t ans = 0;
//     for (int i = 0; i < n; i++) {
//         if (a[i] == 1) {
//             cur_cnt++;
//         }
//         else if (a[i] == 2) {
//             total_cnt += cur_cnt;
//             (total *= 2) %= MOD;
//             (total += total_cnt) %= MOD;
//             cur_cnt = 0;
//         }
//         else {
//             assert(a[i] == 3);
//             (ans += total) %= MOD;
//         }
//     }
//     cout << ans << '\n';
// }

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t = 1;
    cin >> t;
    while (t--) {
        solve_dp();
    }
    return 0;
}
