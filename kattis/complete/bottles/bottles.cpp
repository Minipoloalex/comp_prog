#include <bits/stdc++.h>
using namespace std;

double f_sq(const vector<double> &a, double x) {
    double res = 0, curr = 1;
    for (int i = 0; i < (int) a.size(); i++, curr *= x) {
        res += a[i] * curr;
    }
    return res * res;
}

double compute_volume(vector<double> &a, double xlow, double xhigh) {
    // for (int i = 0; i < (int) a.size(); i++) {
    //     cout << i << ": " << a[i] << endl;
    // }
    int n = 1e4;
    double delta_x = (xhigh - xlow) / (double) n;
    // cout << delta_x << endl;
    double res = 0;
    
    for (int i = 1; i < n; i++) {
        double xi = xlow + i * delta_x;
        if (i % 2 == 1) {   // odd
            res += 4 * f_sq(a, xi);
        }
        else res += 2 * f_sq(a, xi);    // even
    }
    res += f_sq(a, xlow) + f_sq(a, xhigh);
    res *= delta_x/3.0;
    return M_PI * res;
}

int main() {
    cout << fixed << setprecision(2);
    // P > 0, Vx [xlow, xhigh]
    // no more than 8 increments should be marked
    int t = 1;
    int n;
    vector<double> c;
    while (cin >> n) {  // degree n [0, 10]
        c.resize(n + 1);
        for (int i = 0; i <= n; i++) {   // coeficients (double)
            cin >> c[i];
        }
        double xlow, xhigh; // xhigh, xlow [-100, 100] xhigh > xlow
        int inc;    // [1, 500]
        cin >> xlow >> xhigh >> inc;
        double volume = compute_volume(c, xlow, xhigh);
        cout << "Case " << t++ << ": " << volume << endl;
        // increasing sequence of no more than 8 volume markings (or insufficient volume)
        
        vector<double> marks;
        double curr_inc = inc;
        for (int i = 0; i < 8; i++, curr_inc += inc) {
            // search the volume inc
            double a = xlow;
            double b = xhigh;
            for (int _ = 0; _ < 50; _++) {
                double m = (a + b)/2;
                double vol = compute_volume(c, xlow, m);
                if (vol > curr_inc) {
                    b = m;  //  - 0.0001
                }
                else if (vol < curr_inc) {
                    a = m;  //  + 0.0001
                }
                else break;
            }
            if (a <= xhigh - 0.01) marks.push_back(a - xlow);
            else break;
        }
        if (marks.empty()) {
            cout << "insufficient volume";
        }
        for (int m = 0; m < (int) marks.size(); m++) {
            if (m != 0) cout << " ";
            cout << marks[m];
        }
        cout << endl;
    }
    return 0;
}
