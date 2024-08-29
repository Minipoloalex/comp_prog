#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];
        string s;
        cin >> s;
        int l = 0, r = n - 1;

        vector<int64_t> pref(n);
        pref[0] = a[0];
        for (int i = 1; i < n; i++) {
            pref[i] = pref[i - 1] + a[i];
        }
        auto rsq = [&](int i, int j) -> int64_t {
            if (i - 1 >= 0) return pref[j] - pref[i - 1];
            return pref[j];
        };

        int64_t ans = 0;
        while (l <= r) {
            if (s[l] == 'L' && s[r] == 'R') {
                ans += rsq(l, r);
                l++;
                r--;
            }
            else {
                if (s[l] == 'R') l++;
                if (s[r] == 'L') r--;
            }
        }
        cout << ans << '\n';
    }
    return 0;
}
