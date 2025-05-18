#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &x: a) cin >> x;

    int64_t ans = 0;
    for (int b = 0; b < 31; b++) {
        vector<int> pref(n + 1, 0);
        for (int i = 1; i <= n; i++) {
            int ibit = (a[i - 1] >> b) & 1;
            pref[i] = pref[i - 1] ^ ibit;
        }
        for (int i = 1; i <= n; i++) {
            for (int j = i; j <= n; j++) {
                int subseqpref = pref[j] ^ pref[i - 1];
                if (subseqpref) {
                    ans += 1 << b;
                }
            }
        }
    }
    cout << ans - accumulate(a.begin(), a.end(), 0LL) << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    solve();
    return 0;
}
