#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        string a, b;
        cin >> a >> b;

        int n = (int) a.size();
        int m = (int) b.size(); 
        int ans = n + m;

        for (int ib = 0; ib < m; ib++) {
            int matched = 0;
            int ib2 = ib;
            for (int ia = 0; ia < n; ia++) {
                char ca = a[ia];
                if (ib2 < m && b[ib2] == ca) {
                    ib2++;
                    matched++;
                }
            }
            ans = min(ans, n + m - matched);
        }
        cout << ans << endl;
    }
    return 0;
}
