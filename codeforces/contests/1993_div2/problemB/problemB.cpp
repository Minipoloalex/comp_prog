#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        // o + e = o, e + e = e, o + o = e
        int cnt_evens = 0, cnt_odds = 0;

        int64_t mx_odd = 0, mx_even = 0;
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            if (a[i] & 1) {
                mx_odd = max(int(mx_odd), a[i]);
                cnt_odds++;
            }
            else {
                mx_even = max(int(mx_even), a[i]);
                cnt_evens++;
            }
        }
        if (cnt_evens == 0 || cnt_odds == 0) {
            cout << "0\n";
            continue;
        }


        sort(a.begin(), a.end());
        int ans = 0;
        for (int i = 0; i < n; i++) {
            if ((a[i] & 1) == 0) {  // even numbers
                if (a[i] <= mx_odd) {
                    ans++;
                    mx_odd += a[i];
                }
                else {
                    assert(a[i] > mx_odd);
                    mx_odd += mx_even;
                    // instead of using this number, we use the biggest even number
                    // makes sure that we will not need any more of these additional operations
                    ans += 2;
                }
            }
        }
        cout << ans << '\n';
    }
    return 0;
}
