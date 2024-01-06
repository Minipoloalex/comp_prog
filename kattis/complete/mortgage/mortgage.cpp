#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;
const double EPS = 1e-9;

// do not call if r == 1 (in this case if interest rate is 0)
double get_sum_gp(ull n, double r, double a = 1) {
    return a * (1 - pow(r, n)) / (1 - r);
}

int main() {
    double x, y;   // [1, 1e9]
    int n;  // [1, 10000]
    double r; // [0, 100]
    while (cin >> x >> y >> n >> r) {
        if (x == 0 && y == 0 && n == 0 && r == 0) break;
        double second_portion = r == 0 ? n * 12 : get_sum_gp(n * 12, 1 + r/1200.0);
        double capital_n = x * pow(1 + r/1200.0, n * 12) - y * second_portion;
        if (capital_n < EPS) {
            cout << "Yes" << endl;
        }
        else cout << "No" << endl;
    }
    return 0;
}
