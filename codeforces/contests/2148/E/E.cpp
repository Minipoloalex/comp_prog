#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (auto &ai: a) cin >> ai;

    vector<int> freq(n + 1);
    for (auto &ai: a) freq[ai]++;
    for (int i = 0; i < n; i++) {
        if (freq[a[i]] % k > 0) {
            cout << "0\n";
            return;
        }
    }

    vector<int> curfreq(n + 1);
    int64_t ans = 0;
    int l = 0, r = 0;
    while (r < n) {
        curfreq[a[r]]++;
        while (curfreq[a[r]] > freq[a[r]] / k) {
            curfreq[a[l++]]--;
        }
        ans += r - l + 1;
        r++;
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
