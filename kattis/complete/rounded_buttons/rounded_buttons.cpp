#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-9;

struct point {
  double x, y;                                   // if need more precision
  point() { x = y = 0.0; }                       // default constructor
  point(double _x, double _y) : x(_x), y(_y) {}  // constructor
  bool operator < (point other) const {          // override < operator
    if (fabs(x-other.x) > EPS)                   // useful for sorting
      return x < other.x;                        // by x-coordinate
    return y < other.y;                          // if tie, by y-coordinate
  }
  // use EPS (1e-9) when testing equality of two floating points
  bool operator == (point other) const {
   return (fabs(x-other.x) < EPS && (fabs(y-other.y) < EPS));
  }
};

double dist(point p1, point p2) {                // Euclidean distance
  // hypot(dx, dy) returns sqrt(dx*dx + dy*dy)
  return hypot(p1.x-p2.x, p1.y-p2.y);            // return double
}

bool is_inside_rounded_rectangle(double xleft, double ytop, double xright, double ybottom, double r, double xi, double yi) {
    if (xi >= xleft + r && xi <= xright - r && yi >= ytop && yi <= ybottom) return true;
    if (yi >= ytop + r && yi <= ybottom - r && xi >= xleft && xi <= xright) return true;
    vector<point> vp({
        point(xleft + r, ytop + r),   // center_tl
        point(xright - r, ytop + r),  // center_tr
        point(xleft + r, ybottom - r),    // center_bl
        point(xright - r, ybottom - r),   // center_br
    });
    for (int i = 0; i < 4; i++) {
        if (dist(vp[i], point(xi, yi)) <= r) {  // check distance to center of each circle
            return true;
        }
    }
    return false;
}


int main() {
    int n; cin >> n;
    while(n--) {
        double x, y, w, h, r;
        cin >> x >> y >> w >> h >> r;   // xy [0, 1000] wh]0, 1000] 2r [0, min(w, h)]
        int m;
        cin >> m;
        while (m--) {
            double xi, yi;
            cin >> xi >> yi;// [0, 2000]
            if (is_inside_rounded_rectangle(x, y, x + w, y + h, r, xi, yi)) {
                cout << "inside";
            }
            else cout << "outside";
            cout << endl;
        }
        cout << endl;
    }
    return 0;
}
