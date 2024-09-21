#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        string ans;
        if (k % 2 == 0) {   // even size
            if ((k / 2) % 2 == 0) ans = "YES";
            else ans = "NO";
        }
        else {  // odd size
            int first = n - k + 1;
            // int last = n;
            // cout << first << " " << last << " ";
            int total_odds = k / 2;
            if (first % 2 == 1) total_odds++;
            // cout << total_odds << " ";
            if (total_odds % 2 == 0) ans = "YES";
            else ans = "NO";
        }
        cout << ans << '\n';
    }
    return 0;
}
