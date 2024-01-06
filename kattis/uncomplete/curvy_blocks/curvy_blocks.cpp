#include <bits/stdc++.h>
using namespace std;

typedef pair<double, double> dd;

dd get_roots(double a, double b, double c) {
    double rt = sqrt(b * b - 4 * a * c);
    return { (-b + rt)/(2*a), (-b - rt)/(2*a) };
}

double get_value(double a0, double a1, double a2, double a3, double x) {
    return a0 + a1*x + a2*x*x + a3*x*x*x;
}

int main() {
    double b0, b1, b2, b3, t0, t1, t2, t3;
    // max 500 test cases
    while (cin >> b0 >> b1 >> b2 >> b3 >> t0 >> t1 >> t2 >> t3) {   // [-5e4, 5e4]
        dd first_roots = get_roots(b1, 2*b2, 3*b3);
        dd second_roots = get_roots(t1, 2*t2, 3*t3);
        // check for x [0, 1], roots must be in that interval
        // what if there is no root inside that interval? i.e. increasing in x [0, 1]
        double by1 = get_value(b0, b1, b2, b3, first_roots.first);
        double by2 = get_value(b0, b1, b2, b3, first_roots.second);
        double ty1 = get_value(t0, t1, t2, t3, second_roots.first);
        double ty2 = get_value(t0, t1, t2, t3, second_roots.second);
        cout << by1 << " " << by2 << " " << ty1 << " " << ty2 << endl;
    }
    return 0;
}
