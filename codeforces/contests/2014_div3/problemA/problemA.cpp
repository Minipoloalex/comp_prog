#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        int curr = 0, ans = 0;
        for (int i = 0; i < n; i++) {
            int ai;
            cin >> ai;
            if (ai >= k) curr += ai;
            else if (ai == 0 && curr > 0) {
                ans++;
                curr--;
            }
        }
        cout << ans << '\n';
    }
    return 0;
}
