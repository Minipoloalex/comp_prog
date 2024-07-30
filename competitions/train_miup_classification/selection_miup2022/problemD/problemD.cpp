#include <bits/stdc++.h>
using namespace std;
struct point {
  double x, y;                                      // use this if possible
  point() { x = y = 0; }                       // default constructor
  point(double _x, double _y) : x(_x), y(_y) {}      // constructor
};
int insideCircle(point p, point c, int r) {  // all integer version
  double dx = p.x-c.x, dy = p.y-c.y;
  double Euc = dx*dx + dy*dy, rSq = r*r;            // all integer
  return Euc < rSq ? 1 : Euc == rSq ? 0 : -1;    // inside/border/outside
}

int main() {
    int n;
    cin >> n;
    vector<pair<point, int>> circles;
    double sum_area = 0;
    for (int i = 0; i < n; i++) {
        int xi, yi, ri;
        cin >> xi >> yi >> ri;
        double area = M_PI * ri * ri;
        sum_area += area;
        circles.emplace_back(point(xi, yi), ri);
    }
    double area = 0;
    double r = 0.05;
    for (double xi = -10; xi <= 20; xi += r) { // 40 * 1e3
        for (double yi = -10; yi <= 20; yi += r) {  // 40 * 1e3
            point p(xi, yi);
            for (auto &[center, radius]: circles) {
                if (insideCircle(p, center, radius) == 1) {
                    area += r * r;
                    break;
                }
            }
        }
    }
    cout << area << endl;
    return 0;
}
