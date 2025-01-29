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
};
// ax + by + c = 0
// b has only two possible values
// b = 0 -> vertical line (a = 1, x = -c)
// b = 1 -> normal line (y = -ax + -c)
struct line { double a, b, c; };                 // most versatile

// the answer is stored in the third parameter (pass by reference)
void pointsToLine(point p1, point p2, line &l) {
  if (fabs(p1.x-p2.x) < EPS)                     // vertical line is fine
    l = {1.0, 0.0, -p1.x};                       // default values
  else {
    double a = -(double)(p1.y-p2.y) / (p1.x-p2.x);
    l = {a, 1.0, -(double)(a*p1.x) - p1.y};      // NOTE: b always 1.0
  }
}

bool areParallel(line l1, line l2) {             // check a & b
  return (fabs(l1.a-l2.a) < EPS) && (fabs(l1.b-l2.b) < EPS);
}

bool areSame(line l1, line l2) {                 // also check  c
  return areParallel(l1,l2) && (fabs(l1.c-l2.c) < EPS);
}

// returns true (+ intersection point p) if two lines are intersect
bool areIntersect(line l1, line l2, point &p) {
  if (areParallel(l1, l2)) return false;         // no intersection
  // solve system of 2 linear algebraic equations with 2 unknowns
  // using matrix representation (and Cramer's Rule)
  p.x = (l2.b*l1.c - l1.b*l2.c) / (l2.a*l1.b - l1.a*l2.b);

  // special case: test for vertical line to avoid division by zero
  if (fabs(l1.b) > EPS) p.y = -(l1.a*p.x + l1.c); // from y = -ax - c
  else                  p.y = -(l2.a*p.x + l2.c);
  return true;
}
inline bool intersect_1d(double a, double b, double c, double d) {
	if (a > b) { swap(a, b); }  // a = min(a, b), b = max(a, b)
	if (c > d) { swap(c, d); }  // c = min(c, d), d = max(c, d)

  // a, c are the mins
  // b, d are the maxs
  // [max(a, c), min(b, d)] -> represents the intersected space
	return max(a, c) <= min(b, d) + EPS;
}

/*
 * Implemented by _FM
 * Checks if the rectangles formed by the points [p1, p2] and [p3, p4] intersect.
 * Returns true if they collide, false otherwise.
 * Check intersect_1d to get the intersected_space
 */
bool bbox_collision(const point &p1, const point &p2, const point &p3, const point &p4) {
  return intersect_1d(p1.x, p2.x, p3.x, p4.x) && intersect_1d(p1.y, p2.y, p3.y, p4.y);
}

// tests for min(l,r) <= x <= max(l,r), with precision concerns
inline bool betw(double l, double r, double x) {
	return min(l, r) <= x + EPS && x <= max(l, r) + EPS;
}

bool segment_intersection(array<point, 4> &pts, point &left, point &right) {
  auto &[a, b, c, d] = pts;
  if (!bbox_collision(a, b, c, d)) {
    return false;
  }
  line l1, l2;
  pointsToLine(a, b, l1);
  pointsToLine(c, d, l2);

  if (areParallel(l1, l2)) {
    if (!areSame(l1, l2)) return false;

    // same line, intersection can be calculated with bounding boxes
    // p < q, if x smaller (then y smaller)
    if (b < a) { swap(a, b); }  // a = min(a, b), b = max(a, b)
		if (d < c) { swap(c, d); }  // c = min(c, d), d = max(c, d)
		left = max(a, c);
		right = min(b, d);
    return true;
  }
  else {
    point p;
    // lines must intersect (not parallel)
    areIntersect(l1, l2, p);
    if (fabs(p.x) < EPS) p.x = 0; // make -0's be 0
    if (fabs(p.y) < EPS) p.y = 0;

    left = p;
    right = p;
    // account for segment size
    return betw(a.x, b.x, p.x) && betw(a.y, b.y, p.y) &&
           betw(c.x, d.x, p.x) && betw(c.y, d.y, p.y);
  }
}

void solve() {
    array<point, 4> pts;
    for (auto &p: pts) {
        cin >> p;
    }
    vector<point> intersections;
    point left, right;
    if (!segment_intersection(pts, left, right)) {
      cout << "none\n";
    }
    else if (left == right) {
      cout << fixed << setprecision(2) << left.x << " " << left.y << '\n';
    }
    else {
      cout << fixed << setprecision(2) << left.x << " " << left.y << " " << right.x << " " << right.y << '\n';
    }
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
