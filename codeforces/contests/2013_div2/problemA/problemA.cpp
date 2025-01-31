#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        int x, y;
        cin >> x >> y;
        int mn = min(x, y);
        int ans = (n + mn - 1) / mn;
        cout << ans << '\n';
    }
    return 0;
}
