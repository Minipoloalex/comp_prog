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
  bool operator != (point other) const {
    return !(*this == other);
  }
  friend istream &operator>>(istream &iss, point &p) {
    return iss >> p.x >> p.y;
  }
  point operator-(point other) const {
    return {x - other.x, y - other.y};
  }
  double operator*(point other) {
    return x * other.y - y * other.x;
  }
};
double dist(point p1, point p2) {                // Euclidean distance
  // hypot(dx, dy) returns sqrt(dx*dx + dy*dy)
  return hypot(p1.x-p2.x, p1.y-p2.y);            // return double
}
struct vec { double x, y; // name: `vec' is different from STL vector
  vec(double _x, double _y) : x(_x), y(_y) {}
};
vec toVec(const point &a, const point &b) {      // convert 2 points
  return vec(b.x-a.x, b.y-a.y);                  // to vector a->b
}
vec scale(const vec &v, double s) {              // s = [<1..1..>1]
  return vec(v.x*s, v.y*s);                      // shorter/eq/longer
}                                                   // return a new vec
point translate(const point &p, const vec &v) {  // translate p
  return point(p.x+v.x, p.y+v.y);                // according to v
}                                                // return a new point

// returns the dot product of two vectors a and b
double dot(vec a, vec b) { return (a.x*b.x + a.y*b.y); }

// returns the squared value of the normalized vector
double norm_sq(vec v) { return v.x*v.x + v.y*v.y; }

// returns the distance from p to the line defined by
// two points a and b (a and b must be different)
// the closest point is stored in the 4th parameter (byref)
double distToLine(point p, point a, point b, point &c) {
  vec ap = toVec(a, p), ab = toVec(a, b);
  double u = dot(ap, ab) / norm_sq(ab);
  // formula: c = a + u*ab
  c = translate(a, scale(ab, u));                // translate a to c
  return dist(p, c);                             // Euclidean distance
}

// returns the distance from p to the line segment ab defined by
// two points a and b (technically, a has to be different than b)
// the closest point is stored in the 4th parameter (byref)
double distToLineSegment(point p, point a, point b, point &c) {
  vec ap = toVec(a, p), ab = toVec(a, b);
  double u = dot(ap, ab) / norm_sq(ab);

  if (u < 0.0) {                                 // closer to a
    c = point(a.x, a.y);
    return dist(p, a);                           // dist p to a
  }

  // think of projection of P to AB line
  if (u > 1.0) {                                 // closer to b
    c = point(b.x, b.y);
    return dist(p, b);                           // dist p to b
  }
  return distToLine(p, a, b, c);                 // use distToLine
}

// returns the cross product of two vectors a and b
double cross(vec a, vec b) { return a.x*b.y - a.y*b.x; }

bool parallel(vec &v1, vec &v2) {
    return fabs(cross(v1, v2)) < EPS;
}

// returns true if point r is on the same line as the line pq
bool collinear(point p, point q, point r) {
  return fabs(cross(toVec(p, q), toVec(p, r))) < EPS;
}

bool bounding_box_collision(const point &p1, const point &p2, const point &p3, const point &p4) {
    return !(min(p1.x, p2.x) > max(p3.x, p4.x) || min(p1.y, p2.y) > max(p3.y, p4.y) ||
             min(p3.x, p4.x) > max(p1.x, p2.x) || min(p3.y, p4.y) > max(p1.y, p2.y));
}


// Does not allow segments with coincident points
bool intersect(array<point, 4> &p) {
    vec v1 = toVec(p[0], p[1]);
    vec v2 = toVec(p[2], p[3]);

    if (parallel(v1, v2)) {
        if (collinear(p[0], p[1], p[2]) && collinear(p[0], p[1], p[3]) && bounding_box_collision(p[0], p[1], p[2], p[3])) {
            return true;
        }
        return false;
    }

    auto equal_signs = [&](point &p1, point &p2, point &o1, point &o2) -> bool {
        // tells us if segment (o1, o2) is completely on one side of segment (p1, p2)
        // may need to be careful if cross product is zero
        double c1 = cross(toVec(p1, p2), toVec(p1, o1));
        double c2 = cross(toVec(p1, p2), toVec(p1, o2));
        return (c1 > EPS && c2 > EPS) || (c1 < -EPS && c2 < -EPS);  // careful when cross prod is 0
    };

    if (equal_signs(p[0], p[1], p[2], p[3]) || equal_signs(p[2], p[3], p[0], p[1])) {
        return false;
    }
    return true;
}

// the first two points represent a segment
// the other two points represent the other segment
// allows segments with coicident points
double line_segment_distance(array<point, 4> &pts) {
    point ignore;
    if (pts[0] != pts[1] && pts[2] != pts[3] &&
        intersect(pts)) {   // only use intersect if segments have different points
        return 0;
    }

    double ans = DBL_MAX;
    for (int i = 0; i <= 3; i++) {
        int first = i < 2 ? 2: 0;
        point a = pts[first];
        point b = pts[first + 1];
        double d;
        if (a == b) { // if segment is a point
            d = dist(a, pts[i]);
        }
        else d = distToLineSegment(pts[i], a, b, ignore);
        ans = min(ans, d);
    }
    return ans;
}

void solve() {
    array<point, 4> pts;
    for (auto &p: pts) {
        cin >> p;
    }
    double ans = line_segment_distance(pts);
    cout << fixed << setprecision(2) << ans << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
