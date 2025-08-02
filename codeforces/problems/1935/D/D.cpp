#include <bits/stdc++.h>
using namespace std;

void solve() {
    int64_t n, c;
    cin >> n >> c;
    vector<int64_t> s(n);
    array<int64_t,2> freq = {0, 0};
    for (auto &si: s) {
        cin >> si;
        freq[si & 1]++;
    }
    auto calc_C = [&]() {   // x + y = si
        int64_t ans = 0;
        for (int i = 0; i < n; i++) {
            ans += s[i] / 2 + 1;
        }
        return ans;
    };
    auto calc_D = [&]() {   // y - x = si
        int64_t ans = 0;
        for (int i = 0; i < n; i++) {
            ans += c - s[i] + 1;
        }
        return ans;
    };
    auto calc_C_and_D = [&]() { // x + y = si and y - x = sj (i and j can be the same)
        int64_t ans = 0;
        ans += freq[0] * (freq[0] + 1) / 2;
        ans += freq[1] * (freq[1] + 1) / 2;
        return ans;
    };
    int64_t A = (c + 2) * (c + 1) / 2;
    int64_t C = calc_C();
    int64_t D = calc_D();
    int64_t C_and_D = calc_C_and_D();
    int64_t C_or_D = C + D - C_and_D;
    int64_t ans = A - (C_or_D);
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
