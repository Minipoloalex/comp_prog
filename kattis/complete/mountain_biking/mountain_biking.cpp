#include <bits/stdc++.h>
using namespace std;

double DEG_to_RAD(double d) { return d*M_PI/180.0; }

double RAD_to_DEG(double r) { return r*180.0/M_PI; }

struct mountain {
    double a;
    int di;
};

int main() {
    int n;
    double g;
    cin >> n >> g;
    vector<mountain> arr;
    for (int i = 0; i < n; i++) {
        int di, oi;
        cin >> di >> oi;    // segments ordered from top of the hill to the bottom
        double a = g * cos(DEG_to_RAD(oi));
        arr.push_back({a, di});
    }
    
    vector<double> res(n);
    double vi = 0;
    for (int i = n - 1; i >= 0; i--) {   // sqrt(2 * a * di + vi * vi/2);
        double a = arr[i].a;
        int di = arr[i].di;
        res[i] = sqrt(2 * a * di + vi * vi);
        vi = res[i];
    }
    
    cout << fixed << setprecision(10);
    for (double r: res) {
        cout << r << endl;
    }
    return 0;
}
