#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        int ans = 0;
        for (int i = 0; i < n; i++) {
            int ai;
            cin >> ai;
            if (i % 2 == 0) {
                ans += ai;
            }
            else {
                ans -= ai;
            }
        }
        cout << ans << '\n';
    }    
    return 0;
}
