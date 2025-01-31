#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        sort(a.begin(), a.end());
        int mx = a.back();
        vector<int> pref(k, 0);
        // for each of them, we want to place them at an interval [m, m + k - 1]
        // [max_number, max_number + k - 1] Need to test if these minutes will yield a possible result
        for (int i = 0; i < n; i++) {
            int div = (mx + k - 1 - a[i]) / (2 * k);
            int nvalue = a[i] + div * 2 * k;
            if (nvalue >= mx) {
                pref.at(nvalue - mx)++;
            }
            else if (nvalue < mx && nvalue + k - 1 >= mx) {
                pref.at(0)++;
                pref.at(nvalue + k - mx)--;
            }
        }
        int ans = -1;
        if (pref[0] == n) {
            ans = mx;
        }
        else {
            for (int i = 1; i < k; i++) {
                pref[i] += pref[i - 1];
                if (pref[i] == n) {
                    ans = mx + i;
                    break;
                }
            }
        }
        cout << ans << '\n';
    }
    return 0;
}
