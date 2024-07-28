#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);

    int t;
    cin >> t;
    while (t--) {
        string s;
        cin >> s;
        int n = (int) s.size();
        vector<int> pref(n + 1);
        vector<int64_t> tot_sum(2 * n + 10, 0);

        int64_t mod = int64_t(1e9 + 7);

        pref[0] = 0;
        for (int i = 0; i < n; i++) {
            pref[i + 1] = pref[i] + (s[i] == '0' ? 1 : -1);
            // cout << pref[i + 1] << " ";
        }
        // cout << '\n';

        const int not_negative_ensurance = n + 1;

        int64_t ans = 0;
        for (int y = 0; y <= n; y++) {  // exclusive (e.g. 0 includes no item)
            int p = pref[y];
            int tot_sum_idx = p + not_negative_ensurance;

            if (tot_sum_idx < 0) {
                while(1);
                // cout << "BROKEN" << '\n';
            }

            ans = (ans + ((n - y + 1) * tot_sum[tot_sum_idx]) % mod) % mod;

            tot_sum[tot_sum_idx] = (tot_sum[tot_sum_idx] + y + 1) % mod;
        }
        cout << (ans + mod) % mod << '\n';
    }
    return 0;
}
