#include <bits/stdc++.h>
using namespace std;

double dist(int x1, int x2, int y1, int y2) {
    return sqrt((x1 - x2)*(x1 -x2) + (y1 -y2)*(y1-y2));
}

int main() {
    int x1, y1;
    int x2, y2;
    int x3, y3;
    int x4, y4;
    cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;
    double a = dist(x1, x2, y1, y2);
    double b = dist(x3, x4, y3, y4);
    double m = max(a, b);
    cout << fixed << setprecision(10) << m << endl;
    return 0;
}
