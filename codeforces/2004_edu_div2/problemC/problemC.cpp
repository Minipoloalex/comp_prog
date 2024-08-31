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
        for (int i = 0; i < n; i++) cin >> a[i];
        sort(a.rbegin(), a.rend());
        int64_t ans = 0;
        for (int i = 0; i < n; i++) {
            if (i % 2 == 0) {   // A
                ans += a[i];
            }
            else {  // B
                int before = a[i - 1];   // always: before >= curr
                int curr = a[i];
                if (curr + k >= before) {
                    k -= before - curr;
                    curr = before;
                }
                else {
                    curr += k;
                    k = 0;
                }
                ans -= curr;
            }
        }
        cout << ans << '\n';
    }
    return 0;
}
