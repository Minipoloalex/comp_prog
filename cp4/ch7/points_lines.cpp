#include <bits/stdc++.h>
using namespace std;

const double INF = 1e9;
const double EPS = 1e-9;
const double PI = acos(-1.0);

double DEG_to_RAD(double d) { return d*PI/180.0; }
double RAD_to_DEG(double r) { return r*180.0/PI; }

// struct point_i { int x, y; };                 // minimalist mode

// struct point_i {
//   int x, y;                                      // use this if possible
//   point_i() { x = y = 0; }                       // default constructor
//   point_i(int _x, int _y) : x(_x), y(_y) {}      // constructor
// };
// ostream &operator<<(ostream &os, const point_i &p) {
//   return os << "(" << p.x << ", " << p.y << ")";
// }

struct point {
  double x, y;
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

// rotate p by theta degrees CCW w.r.t origin (0, 0)
point rotate(point p, double theta) {
  double rad = DEG_to_RAD(theta);                // convert to radian
  return point(p.x*cos(rad) - p.y*sin(rad),
               p.x*sin(rad) + p.y*cos(rad));
}

// ax + by + c = 0
// b has only two possible values
// b = 0 -> vertical line (a = 1, x = -c)
// b = 1 -> "normal" line (y = -ax + -c)
struct line { double a, b, c; };                 // most versatile

// return by reference
void pointsToLine(point p1, point p2, line &l) {
  if (fabs(p1.x-p2.x) < EPS)                     // vertical line is fine
    l = {1.0, 0.0, -p1.x};                       // default values
  else {
    double a = -(double)(p1.y-p2.y) / (p1.x-p2.x);
    l = {a, 1.0, -(double)(a*p1.x) - p1.y};      // NOTE: b always 1.0
  }
}

// convert point and gradient/slope to line
void pointSlopeToLine(point p, double m, line &l) {
  l.a = -m;                                      // always -m
  l.b = 1;                                       // always 1
  l.c = -((l.a * p.x) + (l.b * p.y));            // compute this
}

// // not needed since we will use the more robust form: ax + by + c = 0
// struct line2 { double m, c; };                   // alternative way

// int pointsToLine2(point p1, point p2, line2 &l) {
//   if (p1.x == p2.x) {                            // vertical line
//     l.m = INF;                                   // this is to denote a
//     l.c = p1.x;                                  // line x = x_value
//     return 0;                                    // differentiate result
//   }
//   else {
//     l.m = (double)(p1.y-p2.y) / (p1.x-p2.x);
//     l.c = p1.y - l.m*p1.x;
//     return 1;                                    // standard y = mx + c
//   }
// }

bool areParallel(line l1, line l2) { // check a & b
  return (fabs(l1.a-l2.a) < EPS) && (fabs(l1.b-l2.b) < EPS);
}

bool areSame(line l1, line l2) { // also check  c
  return areParallel(l1 ,l2) && (fabs(l1.c-l2.c) < EPS);
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

// projection of point p in line l (returned by reference)
void closestPoint(line l, point p, point &ans) {
  // this line is perpendicular to l and pass through p
  line perpendicular;                            
  if (fabs(l.b) < EPS) {                         // vertical line
    ans.x = -(l.c);
    ans.y = p.y;
    return;
  }
  if (fabs(l.a) < EPS) {                         // horizontal line
    ans.x = p.x;
    ans.y = -(l.c);
    return;
  }
  pointSlopeToLine(p, 1/l.a, perpendicular);     // normal line
  // intersect line l with this perpendicular line
  // the intersection point is the closest point
  areIntersect(l, perpendicular, ans);
}

struct vec { double x, y;
  vec(double _x, double _y) : x(_x), y(_y) {}
};
vec toVec(const point &a, const point &b) {      // convert 2 points
  return vec(b.x-a.x, b.y-a.y);                  // to vector a->b
}
vec scale(const vec &v, double s) {              // s = [<1..1..>1]
  return vec(v.x*s, v.y*s);                      // shorter/eq/longer
}
point translate(const point &p, const vec &v) {  // translate p
  return point(p.x+v.x, p.y+v.y);                // according to v
}

// returns the reflection of point on a line
void reflectionPoint(line l, point p, point &ans) {
  point b;
  closestPoint(l, p, b);                         // similar to distToLine
  vec v = toVec(p, b);                           // create a vector
  ans = translate(translate(p, v), v);           // translate p twice
}

// returns the dot product of two vectors a and b
double dot(vec a, vec b) { return (a.x*b.x + a.y*b.y); }

// returns the squared value of the normalized vector
double norm_sq(vec v) { return v.x*v.x + v.y*v.y; }

double angle(const point &a, const point &o, const point &b) {
  vec oa = toVec(o, a), ob = toVec(o, b);        // a != o != b
  return acos(dot(oa, ob) / sqrt(norm_sq(oa) * norm_sq(ob)));
}                                                // angle aob in rad

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
// two points a and b (a has to be different than b)
// the closest point is stored in the 4th parameter (byref)
double distToLineSegment(point p, point a, point b, point &c) {
  // assert(a != b);
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

// Implemented by _FM
// Assumes v1 != (0, 0), v2 != (0, 0)
bool parallel(vec &v1, vec &v2) {
  return fabs(cross(v1, v2)) < EPS;
}

// note: to accept collinear points, we have to change the `> 0'
// returns true if point r is on the left side of line pq
bool ccw(point p, point q, point r) {
  return cross(toVec(p, q), toVec(p, r)) > -EPS;
}

// returns true if point r is on the same line as the line pq
bool collinear(point p, point q, point r) {
  return fabs(cross(toVec(p, q), toVec(p, r))) < EPS;
}

// Matrix determinant
// [[a b]
//  [c d]]
double det(double a, double b, double c, double d) { return a * d - b * c; }

inline bool intersect_1d(double a, double b, double c, double d) {
	if (a > b) { swap(a, b); }
	if (c > d) { swap(c, d); }

  // a, c are the mins
  // b, d are the maxs
  // [max(a, c), min(b, d)] -> represents the intersected space
	return max(a, c) <= min(b, d) + EPS;
}

// Implemented by _FM
// Checks if the rectangles formed by the points [p1, p2] and [p3, p4] intersect.
// Returns true if they collide, false otherwise.
bool bbox_collision(const point &p1, const point &p2, const point &p3, const point &p4) {
  return intersect_1d(p1.x, p2.x, p3.x, p4.x) && intersect_1d(p1.y, p2.y, p3.y, p4.y);
}

// tests for min(l,r) <= x <= max(l,r), with precision concerns
inline bool betw(double l, double r, double x) {
	return min(l, r) <= x + EPS && x <= max(l, r) + EPS;
}

// Implemented by _FM
// Segments are given by [p[0], p[1]] and [p[2], p[3]]
// Precision: tested with integer points with <= 1e4 absolute value.
// Easily modifiable to work with exact integer values.
// Does not allow segments with coincident points.
// Returns true or false (does not return intersection point)
bool segment_intersection(const array<point, 4> &p) {
    vec v1 = toVec(p[0], p[1]);
    vec v2 = toVec(p[2], p[3]);
    if (parallel(v1, v2)) {
        if (collinear(p[0], p[1], p[2]) && collinear(p[0], p[1], p[3]) && bbox_collision(p[0], p[1], p[2], p[3])) {
            return true;
        }
        return false;
    }
    auto equal_signs = [&](const point &p1, const point &p2, const point &o1, const point &o2) -> bool {
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

// Implemented by _FM
// Another version of segment intersection
// Precision: Tested with integer points with <= 1e4 absolute value
// Can return an intersected segment (if segments partially coincide)
// Returns intersection points left and right by reference
bool segment_intersection(const array<point, 4> &pts, point &left, point &right) {
  auto [a, b, c, d] = pts;
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

int main() {
  vector<point> P;
  P.emplace_back(2e-9, 0);                       // largest
  P.push_back({0, 2});                           // smallest
  P.push_back({1e-9, 1});                        // second smallest
  sort(P.begin(), P.end());
  for (auto &pt : P)                             // the result is
    printf("%.9lf, %.9lf\n", pt.x, pt.y);        // unexpected
  // change
  // const double EPS = 1e-9;
  // to
  // const double EPS = 1e-10;
  // to fix that issue, Rule of Thumb: check the required precision

  point P1, P2, P3(0, 1); // note that both P1 and P2 are (0.00, 0.00)
  printf("%d\n", P1 == P2);                      // true
  printf("%d\n", P1 == P3);                      // false

  P.clear();
  P.push_back(point(2, 2));
  P.push_back(point(4, 3));
  P.push_back(point(2, 4));
  P.push_back(point(6, 6));
  P.push_back(point(2, 6));
  P.push_back(point(6, 5));

  // sorting points demo
  sort(P.begin(), P.end());
  for (int i = 0; i < (int)P.size(); i++)
    printf("(%.2lf, %.2lf)\n", P[i].x, P[i].y);

  // rearrange the points as shown in the diagram below
  P.clear();
  P.push_back(point(2, 2));
  P.push_back(point(4, 3));
  P.push_back(point(2, 4));
  P.push_back(point(6, 6));
  P.push_back(point(2, 6));
  P.push_back(point(6, 5));
  P.push_back(point(8, 6));

  /*
  // the positions of these 7 points (0-based indexing)
  6   P4      P3  P6
  5           P5
  4   P2
  3       P1
  2   P0
  1
  0 1 2 3 4 5 6 7 8
  */

  double d = dist(P[0], P[5]);
  printf("Euclidean distance between P[0] and P[5] = %.2lf\n", d); // should be 5.000

  // line equations
  line l1, l2, l3, l4;
  pointsToLine(P[0], P[1], l1);
  printf("%.2lf * x + %.2lf * y + %.2lf = 0.00\n", l1.a, l1.b, l1.c); // should be -0.50 * x + 1.00 * y - 1.00 = 0.00

  pointsToLine(P[0], P[2], l2); // a vertical line, not a problem in "ax + by + c = 0" representation
  printf("%.2lf * x + %.2lf * y + %.2lf = 0.00\n", l2.a, l2.b, l2.c); // should be 1.00 * x + 0.00 * y - 2.00 = 0.00

  // parallel, same, and line intersection tests
  pointsToLine(P[2], P[3], l3);
  printf("l1 & l2 are parallel? %d\n", areParallel(l1, l2)); // no
  printf("l1 & l3 are parallel? %d\n", areParallel(l1, l3)); // yes, l1 (P[0]-P[1]) and l3 (P[2]-P[3]) are parallel

  pointsToLine(P[2], P[4], l4);
  printf("l1 & l2 are the same? %d\n", areSame(l1, l2)); // no
  printf("l2 & l4 are the same? %d\n", areSame(l2, l4)); // yes, l2 (P[0]-P[2]) and l4 (P[2]-P[4]) are the same line (note, they are two different line segments, but same line)
  
  point p12;
  bool res = areIntersect(l1, l2, p12); // yes, l1 (P[0]-P[1]) and l2 (P[0]-P[2]) are intersect at (2.0, 2.0)
  printf("l1 & l2 are intersect? %d, at (%.2lf, %.2lf)\n", res, p12.x, p12.y);

  // other distances
  point ans;
  d = distToLine(P[0], P[2], P[3], ans);
  printf("Closest point from P[0] to line         (P[2]-P[3]): (%.2lf, %.2lf), dist = %.2lf\n", ans.x, ans.y, d);
  closestPoint(l3, P[0], ans);
  printf("Closest point from P[0] to line V2      (P[2]-P[3]): (%.2lf, %.2lf), dist = %.2lf\n", ans.x, ans.y, dist(P[0], ans));

  d = distToLineSegment(P[0], P[2], P[3], ans);
  printf("Closest point from P[0] to line SEGMENT (P[2]-P[3]): (%.2lf, %.2lf), dist = %.2lf\n", ans.x, ans.y, d); // closer to A (or P[2]) = (2.00, 4.00)
  d = distToLineSegment(P[1], P[2], P[3], ans);
  printf("Closest point from P[1] to line SEGMENT (P[2]-P[3]): (%.2lf, %.2lf), dist = %.2lf\n", ans.x, ans.y, d); // closer to midway between AB = (3.20, 4.60)
  d = distToLineSegment(P[6], P[2], P[3], ans);
  printf("Closest point from P[6] to line SEGMENT (P[2]-P[3]): (%.2lf, %.2lf), dist = %.2lf\n", ans.x, ans.y, d); // closer to B (or P[3]) = (6.00, 6.00)

  reflectionPoint(l4, P[1], ans);
  printf("Reflection point from P[1] to line      (P[2]-P[4]): (%.2lf, %.2lf)\n", ans.x, ans.y); // should be (0.00, 3.00)

  printf("Angle P[0]-P[4]-P[3] = %.2lf\n", RAD_to_DEG(angle(P[0], P[4], P[3]))); // 90 degrees
  printf("Angle P[0]-P[2]-P[1] = %.2lf\n", RAD_to_DEG(angle(P[0], P[2], P[1]))); // 63.43 degrees
  printf("Angle P[4]-P[3]-P[6] = %.2lf\n", RAD_to_DEG(angle(P[4], P[3], P[6]))); // 180 degrees

  printf("P[0], P[2], P[3] form A left turn? %d\n", ccw(P[0], P[2], P[3])); // no
  printf("P[0], P[3], P[2] form A left turn? %d\n", ccw(P[0], P[3], P[2])); // yes

  printf("P[0], P[2], P[3] are collinear? %d\n", collinear(P[0], P[2], P[3])); // no
  printf("P[0], P[2], P[4] are collinear? %d\n", collinear(P[0], P[2], P[4])); // yes

  point p(3, 7), q(11, 13), r(35, 30); // collinear if r(35, 31)
  printf("r is on the %s of line p-q (direction p->q)\n", ccw(p, q, r) ? "left" : "right"); // right

  /*
  // the positions of these 6 points
     E<--  4
           3       B D<--
           2   A C
           1
  -4-3-2-1 0 1 2 3 4 5 6
          -1
          -2
   F<--   -3
  */

  // translation
  point A(2.0, 2.0);
  point B(4.0, 3.0);
  vec v = toVec(A, B); // imagine there is an arrow from A to B (see the diagram above)
  point C(3.0, 2.0);
  point D = translate(C, v); // D will be located in coordinate (3.0 + 2.0, 2.0 + 1.0) = (5.0, 3.0)
  printf("D = (%.2lf, %.2lf)\n", D.x, D.y);
  point E = translate(C, scale(v, 0.5)); // E will be located in coordinate (3.0 + 1/2 * 2.0, 2.0 + 1/2 * 1.0) = (4.0, 2.5)
  printf("E = (%.2lf, %.2lf)\n", E.x, E.y);

  // rotation
  printf("B = (%.2lf, %.2lf)\n", B.x, B.y); // B = (4.0, 3.0)
  point F = rotate(B, 90); // rotate B by 90 degrees COUNTER clockwise, F = (-3.0, 4.0)
  printf("F = (%.2lf, %.2lf)\n", F.x, F.y);
  point G = rotate(B, 180); // rotate B by 180 degrees COUNTER clockwise, G = (-4.0, -3.0)
  printf("G = (%.2lf, %.2lf)\n", G.x, G.y);

  return 0;
}
