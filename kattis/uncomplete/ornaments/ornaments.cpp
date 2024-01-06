#include <bits/stdc++.h>
using namespace std;

int main() {
    int r, h, s;
    while (cin >> r >> h >> s) {
        if (r == 0 && h == 0 && s == 0) break;
        double res = 2 * sqrt(h*h - r*r);
        // cout << 2 * M_PI - 2 * acos(r/h) << endl;
        // res += 2 * (M_PI - acos(r / h)) * r;
        double angle = 360 - 2 * acos(r/h) * (180 / M_PI);
        res += 2 * M_PI * (angle/360) * r;
        cout << res << endl;
        
        res += res * (s / 100);
        // res *= (100 + s);
        cout << fixed << setprecision(2) << res << endl;
    }
    return 0;
}
