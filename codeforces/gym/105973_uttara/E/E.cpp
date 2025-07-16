#include <bits/stdc++.h>
using namespace std;

struct point {
    double x, y;
};

double dist(point p1, point p2) {
  return hypot(p1.x-p2.x, p1.y-p2.y);
}

double perimeter(double ab, double bc, double ca) {
  return ab + bc + ca;
}

double area(point a, point b, point c) {
  return fabs((b.x-a.x)*(c.y-a.y) - (b.y-a.y)*(c.x-a.x)) * 0.5;
}

// compute the intersection point between line segment p-q and line A-B
bool intersects(point p, point q, point A, point B) {
  double a = B.y - A.y, b = A.x - B.x, c = B.x * A.y - A.x * B.y;
  double u = a * p.x + b * p.y + c;
  double v = a * q.x + b * q.y + c;
  return u * v <= 0; // they are on opposite sides or on the line
}
point lineIntersectSeg(point p, point q, point A, point B) {
  double a = B.y-A.y, b = A.x-B.x, c = B.x*A.y - A.x*B.y;
  double u = fabs(a*p.x + b*p.y + c);
  double v = fabs(a*q.x + b*q.y + c);
  return point{(p.x*v + q.x*u) / (u+v), (p.y*v + q.y*u) / (u+v)};
}

const double EPS = 1e-8;    // TLE if we use 1e-12

void solve() {
    int n;
    cin >> n;
    vector<point> ps(n);
    int mny = INT_MAX, mxy = 0;
    for (auto &[x, y]: ps) {
        int xint, yint;
        cin >> xint >> yint;    // [IMPORTANT]: read input as ints (avoid TLE)
        x = xint;
        y = yint;
        mny = min(mny, yint);
        mxy = max(mxy, yint);
    }
    auto max_area = [&](double x, double y) {
        double mx = 0;
        for (int i = 0; i < n; i++) {
            double cur_area = area(point{x,y}, ps[i], ps[(i + 1) % n]);
            mx = max(mx, cur_area);
        }
        return mx;
    };
    auto best_area = [&](double y) {
        double lox = INT_MAX, hix = INT_MIN;
        point horz_line1 = point{0, y};
        point horz_line2 = point{100, y};
        for (int i = 0; i < n; i++) {
            point &a = ps[i];
            point &b = ps[(i + 1) % n];
            if (intersects(a,b,horz_line1,horz_line2)) {
                point p = lineIntersectSeg(a,b,horz_line1,horz_line2);
                lox = min(lox, p.x);
                hix = max(hix, p.x);
            }
        }
        while (lox + EPS < hix) {
            double m1x = lox + (hix - lox) / 3;
            double m2x = hix - (hix - lox) / 3;
            if (max_area(m1x, y) < max_area(m2x, y)) {
                hix = m2x;
            }
            else {
                lox = m1x;
            }
        }
        return max_area(lox, y);
    };
    double loy = mny, hiy = mxy;
    while (loy + EPS < hiy) {
        double m1y = loy + (hiy - loy) / 3;
        double m2y = hiy - (hiy - loy) / 3;

        double res_m1 = best_area(m1y);
        double res_m2 = best_area(m2y);
        if (res_m1 < res_m2) {
            hiy = m2y;
        }
        else {
            loy = m1y;
        }
    }
    cout << fixed << setprecision(10) << best_area(loy) << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
