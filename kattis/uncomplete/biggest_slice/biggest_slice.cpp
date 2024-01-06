#include <bits/stdc++.h>
using namespace std;

#define EPS 1e-9

int main() {
    int m;
    cin >> m;
    while (m--) {
        int r, n;
        cin >> r >> n; // r [1, 100] n [1, 10^8]
        int o_degree, o_min, o_sec;
        cin >> o_degree >> o_min >> o_sec;
        double degree = o_degree + o_min/60.0 + o_sec/3600.0;
        
        double total = 360;
        double remainder = total - degree * n;
        // if remainder = 0, then max_degree = degree (+/- imprecision)
         
        double max_degree = degree;
        if (remainder > 0) {
            // there is a remainder after serving all, max_degree corresponds to last slice with the bonus remainder
            // if degree = 0, then remainder = total and max_degree = total
            max_degree = degree + remainder;
        }
        else if (remainder < 0) {
            // not enough to serve all, max_degree is given degree
            max_degree = degree;
        }
        // A = r^2 * degree/2
        double area = r * r * M_PI * max_degree / 360.0;
        cout << fixed << setprecision(6) << area << endl;
    }
    return 0;
}
