#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int a, b;
        cin >> a >> b;

        bool aeven = a % 2 == 0, beven = b % 2 == 0;
        string ans;
        if (aeven && beven) {
            ans = "YES";
        }
        else if (!aeven) {
            ans = "NO";
        }
        else {
            assert(aeven && !beven);
            if (a < 2) ans = "NO";
            else ans = "YES";
        }
        cout << ans << '\n';
    }
    return 0;
}
