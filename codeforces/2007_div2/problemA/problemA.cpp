#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int l, r;
        cin >> l >> r;
        int ans = 0;
        int cnt = 0;
        for (int i = l; i <= r; i++) {
            if (cnt == 0 && i % 2 == 1) cnt++;
            else if (cnt == 1 && i % 2 == 0) cnt++;
            else if (cnt == 2 && i % 2 == 1) {
                cnt = 0;
                ans++;
            }
        }
        cout << ans << '\n';
    }
    return 0;
}
