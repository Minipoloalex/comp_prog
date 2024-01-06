#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    int a, b, s, m, n;
    while (cin >> a >> b >> s >> m >> n) {  // all [1, 10^4]
        if (a == 0 && b == 0 && s == 0 && m == 0 && n == 0) break;
        double x_dist = m * a;
        double y_dist = n * b;

        // angle from ratio y/x
        double angle = atan2(y_dist, x_dist) * 180 / M_PI;
        double v = hypot(x_dist, y_dist) / s;
        cout << fixed << setprecision(2) << angle << " " << v << endl;
    }
    return 0;
}
