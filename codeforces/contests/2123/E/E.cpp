#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &ai: a) cin >> ai;
    sort(a.begin(), a.end());
    vector<int> cnt(n + 1, 0);
    for (int i = 0; i < n; i++) {
        cnt[a[i]]++;
    }
    int max_mex = 0;
    for (int i = 0; i < n; i++) {
        if (cnt[i] > 0 && i == max_mex) max_mex++;
    }
    vector<int> freqcnt(n + 1, 0);
    for (int i = 0; i < n; i++) {
        if (cnt[i] > 0 && i < max_mex) {
            freqcnt[cnt[i]]++;
        }
    }
    int cur = 1;
    for (int k = 0; k <= n; k++) {
        int cnt_max = n - k;  // leave 0 1 2 ... (max_mex-1)
        cur += freqcnt[k];
        int ans = min(cur, cnt_max + 1);
        cout << ans << " \n"[k == n];
    }
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
