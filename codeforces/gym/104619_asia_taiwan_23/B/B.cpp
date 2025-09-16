#include <bits/stdc++.h>
using namespace std;

void solve() {
    int r1, r2; double s1d, s2d;
    cin >> r1 >> r2 >> s1d >> s2d;
    int s1 = round(s1d * 100);
    int s2 = round(s2d * 100);
    r1--;r2--;
    if (r1 * s2 == r2 * s1) {
        cout << "SAME\n";
    }
    else if (r1 / s1d < r2 / s2d) {
        cout << "TAOYUAN\n";
    }
    else {
        cout << "JAKARTA\n";
    }
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
