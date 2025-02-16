#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-7;

void solve() {
    double sx, sy, tx, ty, cx, cy, r;
    cin >> sx >> sy >> tx >> ty >> cx >> cy >> r;
    double circle_area = 3.14159265358979323846 * r * r;
    auto left_small = [&](double x) -> bool {
        double left = (x - sx) * (ty - sy);
        double right = (tx - x) * (ty - sy);
        if (x > cx + r) {
            left -= circle_area;
        }
        else if (x < cx - r) {
            right -= circle_area;
        }
        else {
            // x inside circle
            double d = fabs(x - cx);
            double half_theta = acos(d / r);

            double half_c = r * sin(half_theta);
            double triangle_area = d * half_c;
            double arc_area = half_theta * r * r;
            double rest_area = arc_area - triangle_area;
            if (x < cx) {
                left -= rest_area;
                right -= circle_area - rest_area;
            }
            else {
                // x > cx
                left -= circle_area - rest_area;
                right -= rest_area;
            }
        }
        return left < right;
    };
    double lo = sx, hi = tx;
    while (hi - lo > EPS) {
        double m = (lo + hi) / 2;
        if (left_small(m)) {
            lo = m;
        }
        else {
            hi = m;
        }
    }
    cout << fixed << setprecision(4) << lo << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    solve();
    return 0;
}
