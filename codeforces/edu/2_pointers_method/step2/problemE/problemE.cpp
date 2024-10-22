#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 1e5;

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i]--;
    }

    vector<int> cnt(MAX_N, 0);
    int curr = 0;
    int l = 0, r = 0;
    int64_t ans = 0;
    while (r < n) {
        cnt[a[r]]++;
        if (cnt[a[r]] == 1) curr++;
        r++;

        while (curr > k && l < n) {
            cnt[a[l]]--;
            if (cnt[a[l]] == 0) curr--;
            l++;
        }
        if (curr <= k) {
            ans += (r - l);
        }
    }
    cout << ans << '\n';
    return 0;
}
