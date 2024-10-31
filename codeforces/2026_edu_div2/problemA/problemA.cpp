#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int x, y, k;
        cin >> x >> y >> k;
        int mn = min(x, y);
        cout << "0 0 " << mn << " " << mn << '\n';
        cout << "0 " << mn << " " << mn << " 0\n";
    }
    return 0;
}
