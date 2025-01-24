#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &x: a) cin >> x;

    int64_t ans = 0;
    for (int b = 0; b < 31; b++) {
        int pref = 0;
        vector<int> freq = {1, 0};
        for (int i = 0; i < n; i++) {
            int bit = (a[i] >> b) & 1;
            pref ^= bit;

            // add the frequency of the different bit
            // because we want a subarray with bit 1
            ans += freq[pref ^ 1] * 1LL << b;
            freq[pref]++;
        }
    }
    cout << ans - accumulate(a.begin(), a.end(), 0LL) << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    solve();
    return 0;
}
