#include <bits/stdc++.h>
using namespace std;

using f64 = double;
constexpr f64 pi = 3.14159265358979323846;
constexpr f64 eps = 1e-7;

constexpr f64 circular_sector_area(f64 alpha, f64 r) {
    return r * r * alpha * 0.5;
}

void solve() {
    int st, lt, sb, lb; cin >> st >> lt >> sb >> lb;

    f64 sides_top = f64(st);
    f64 length_top = f64(lt);
    f64 sides_bottom = f64(sb);
    f64 length_bottom = f64(lb);

    f64 top_angle_inside_half = pi / sides_top;
    f64 bottom_angle_inside_half = pi / sides_bottom;

    f64 aptop = length_top * 0.5 / tan(top_angle_inside_half);
    f64 apbottom = length_bottom * 0.5 / tan(bottom_angle_inside_half);

    f64 area_bottom = apbottom * sides_bottom * length_bottom * 0.5;
    f64 circle_area_top = pi * aptop * aptop;

    f64 r = aptop;
    f64 a = 0, b = 1, c = -apbottom;
    f64 x0 = -a * c / (a * a + b * b);
    if (c * c > r * r * (a * a + b * b) + eps || abs(c * c - r * r * (a * a + b * b)) < eps) {
        f64 ans = area_bottom - circle_area_top;

        cout << ans << '\n';
    }
    else {
        f64 d = r * r - c * c / (a * a + b * b);
        f64 mult = sqrt(d / (a * a + b * b));
        f64 ax = x0 + b * mult, bx = x0 - b * mult;

        f64 intersection = 2 * max(ax, bx);

        if (intersection > length_bottom) {
            cout << "0.00\n";
            return;
        }

        f64 triangle_area_inside = apbottom * intersection / 2;

        f64 teta = 2 * atan2(intersection / 2, apbottom);
        f64 smaller_circular_area = circular_sector_area(teta, aptop);
        f64 slice_area = smaller_circular_area - triangle_area_inside;

        f64 ans = area_bottom - circle_area_top + sides_bottom * slice_area;
        cout << ans << '\n';
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cout << fixed << setprecision(6);
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
