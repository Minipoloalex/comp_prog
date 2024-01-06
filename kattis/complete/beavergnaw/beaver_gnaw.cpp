#include <bits/stdc++.h>
using namespace std;

int main() {
    // cylinder diameter = height
    double D, V;
    while (cin >> D >> V) { // D [1, 100] V [1, 10^9]
        if (D == 0 && V == 0) break;
        double D_cube = pow(D, 3);
        
        double second = 6.0 * V / M_PI;
        double d = pow(D_cube - second, 1.0/3);
        cout << fixed << setprecision(10) << d << endl;
    }
    return 0;
}
