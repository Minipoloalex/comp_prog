#include <bits/stdc++.h>
using namespace std;

double func(double a, double b, double x) {
    // a * e^(-x^2) + b * sqrt(x)
    return pow(a * exp(-x*x) + b * sqrt(x), 2);
    
}

// integral of PI * r^2 (PI removed but squared remains inside)
double compute_volume(double a, double b, double h) {
    double xlow = 0;
    double xhigh = h;
    int n = 1e6;
    double delta_x = h / n;
    double res = 0;
    for (int i = 1; i < n; i++) {
        double xi = xlow + i * delta_x;
        if (i % 2 == 1) {
            res += 4 * func(a, b, xi);
        }
        else res += 2 * func(a, b, xi);
    }
    res += func(a, b, xlow) + func(a, b, xhigh);
    res *= delta_x / 3.0;
    return M_PI * res;
}

int main() {
    double V;   // V ]0, 10^5]
    int n;  // N ]0, 5]
    cin >> V >> n;
    double min_diff = 1e15;
    int sol_idx = -1;
    for (int i = 0; i < n; i++) {
        double ai, bi, hi;  // [0, 10] [0, 10] [1, 10]
        cin >> ai >> bi >> hi;
        double vol = compute_volume(ai, bi, hi);
        if (fabs(V - vol) < min_diff) {
            min_diff = fabs(V - vol);
            sol_idx = i;
        }
    }
    if (sol_idx == -1) while(1);
    cout << sol_idx << endl;
    return 0;
}
