#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int,int> ii;
#define nx(i) ((i)+1)%n
#define pv(i) ((i)-1+n)%n

const double EPS = 1e-9;

double DEG_to_RAD(double d) { return d*M_PI / 180.0; }

double RAD_to_DEG(double r) { return r*180.0 / M_PI; }

struct point { double x, y;   // only used if more precision is needed
  point() { x = y = 0.0; }                      // default constructor
  point(double _x, double _y) : x(_x), y(_y) {}        // user-defined
  bool operator == (point other) const {
   return (fabs(x-other.x) < EPS && (fabs(y-other.y) < EPS)); } 
  bool operator <(const point &p) const {
   return x < p.x || (abs(x-p.x) < EPS && y < p.y); } };

ostream &operator<<(ostream &os, const point &p) {
  return os << "(" << p.x << ", " << p.y << ")";
}

struct vec { double x, y;  // name: `vec' is different from STL vector
  vec(double _x, double _y) : x(_x), y(_y) {} };

vec toVec(point a, point b) {       // convert 2 points to vector a->b
  return vec(b.x-a.x, b.y-a.y); }

double dist(point p1, point p2) {                // Euclidean distance
  return hypot(p1.x-p2.x, p1.y-p2.y); }               // return double

// returns the perimeter of polygon P, which is the sum of
// Euclidian distances of consecutive line segments (polygon edges)
double perimeter(const vector<point> &P) {       // by ref for efficiency
  double ans = 0.0;
  for (int i = 0; i < (int)P.size()-1; ++i)      // note: P[n-1] = P[0]
    ans += dist(P[i], P[i+1]);                   // as we duplicate P[0]
  return ans;
}
// returns the area of polygon P
double area(const vector<point> &P) {
  double ans = 0.0;
  for (int i = 0; i < (int)P.size()-1; ++i)      // Shoelace formula
    ans += (P[i].x*P[i+1].y - P[i+1].x*P[i].y);
  return fabs(ans)/2.0;                          // only do / 2.0 here
}

double dot(vec a, vec b) { return (a.x*b.x + a.y*b.y); }

double norm_sq(vec v) { return v.x*v.x + v.y*v.y; }

double angle(point a, point o, point b) {  // returns angle aob in rad
  vec oa = toVec(o, a), ob = toVec(o, b);
  return acos(dot(oa, ob) / sqrt(norm_sq(oa) * norm_sq(ob))); }

double cross(vec a, vec b) { return a.x*b.y - a.y*b.x; }

// returns the area of polygon P, which is half the cross products
// of vectors defined by edge endpoints
double area_alternative(const vector<point> &P) {
  double ans = 0.0; point O(0.0, 0.0);           // O = the Origin
  for (int i = 0; i < (int)P.size()-1; ++i)      // sum of signed areas
    ans += cross(toVec(O, P[i]), toVec(O, P[i+1]));
  return fabs(ans)/2.0;
}

// note: to accept collinear points, we have to change the `> 0'
// returns true if point r is on the left side of line pq
bool ccw(point p, point q, point r) {
  return cross(toVec(p, q), toVec(p, r)) > 0;
}

// returns true if point r is on the same line as the line pq
bool collinear(point p, point q, point r) {
  return fabs(cross(toVec(p, q), toVec(p, r))) < EPS;
}

// returns true if we always make the same turn
// while examining all the edges of the polygon one by one
bool isConvex(const vector<point> &P) {
  int n = (int)P.size();
  // a point/sz=2 or a line/sz=3 is not convex  
  if (n <= 3) return false;
  bool firstTurn = ccw(P[0], P[1], P[2]);        // remember one result,
  for (int i = 1; i < n-1; ++i)                 // compare with the others
    if (ccw(P[i], P[i+1], P[(i+2) == n ? 1 : i+2]) != firstTurn)
      return false;                              // different -> concave
  return true;                                   // otherwise -> convex
}

// returns 1/0/-1 if point p is inside/on (vertex/edge)/outside of
// either convex/concave polygon P
int insidePolygon(point pt, const vector<point> &P) {
  int n = (int)P.size();
  if (n <= 3) return -1;                         // avoid point or line
  bool on_polygon = false;
  for (int i = 0; i < n-1; ++i)                  // on vertex/edge?
    if (fabs(dist(P[i], pt) + dist(pt, P[i+1]) - dist(P[i], P[i+1])) < EPS)
      on_polygon = true;
  if (on_polygon) return 0;                      // pt is on polygon
  double sum = 0.0;                              // first = last point
  for (int i = 0; i < n-1; ++i) {
    if (ccw(pt, P[i], P[i+1]))
      sum += angle(P[i], pt, P[i+1]);            // left turn/ccw
    else
      sum -= angle(P[i], pt, P[i+1]);            // right turn/cw
  }
  return fabs(sum) > M_PI ? 1 : -1;              // 360d->in, 0d->out
}

// compute the intersection point between line segment p-q and line A-B
point lineIntersectSeg(point p, point q, point A, point B) {
  double a = B.y-A.y, b = A.x-B.x, c = B.x*A.y - A.x*B.y;
  double u = fabs(a*p.x + b*p.y + c);
  double v = fabs(a*q.x + b*q.y + c);
  return point((p.x*v + q.x*u) / (u+v), (p.y*v + q.y*u) / (u+v));
}

// cuts polygon Q along the line formed by point A->point B (order matters)
// (note: the last point must be the same as the first point)
vector<point> cutPolygon(point A, point B, const vector<point> &Q) {
  vector<point> P;
  for (int i = 0; i < (int)Q.size(); ++i) {
    double left1 = cross(toVec(A, B), toVec(A, Q[i])), left2 = 0;
    if (i != (int)Q.size()-1) left2 = cross(toVec(A, B), toVec(A, Q[i+1]));
    if (left1 > -EPS) P.push_back(Q[i]);         // Q[i] is on the left
    if (left1*left2 < -EPS)                      // crosses line AB
      P.push_back(lineIntersectSeg(Q[i], Q[i+1], A, B));
  }
  if (!P.empty() && !(P.back() == P.front()))
    P.push_back(P.front());                      // wrap around
  return P;
}

vector<point> CH_Andrew(vector<point> &Pts) {    // overall O(n log n)
  int n = (int) Pts.size(), k = 0;
  vector<point> H(2*n);
  sort(Pts.begin(), Pts.end());                  // sort the points by x/y
  for (int i = 0; i < n; ++i) {                  // build lower hull
    while ((k >= 2) && !ccw(H[k-2], H[k-1], Pts[i])) --k;
    H[k++] = Pts[i];
  }
  for (int i = n-2, t = k+1; i >= 0; --i) {       // build upper hull
    while ((k >= t) && !ccw(H[k-2], H[k-1], Pts[i])) --k;
    H[k++] = Pts[i];
  }
  H.resize(k);
  return H;
}

int sign(ll num) {
    if (num < 0) return -1;
    else if (num == 0) return 0;
    else return 1;
}

// Takes in a convex polygon where the last vertex is not repeated
// Note that the CH returns a repeated last vertex
// Returns all pairs of indices of antipodal pairs
// Only valid for p.size() >= 3;
// Does not handle points with precision problems (assumes integer coordinates)
vector<ii> all_anti_podal(const vector<point> &p) {
    int n = (int) p.size();
    assert(n >= 3);

    int p1 = 0, p2 = 0; // two "pointers"
    vector<ii> ans;

    // parallel edges should't be visited twice
    vector<bool> vis(n, false);

    for (;p1<n;p1++) {
        // the edge that we are going to consider in this iteration
        // the datatype is Point, but it acts as a vector
        // point base = p[nx(p1)] - p[p1];
        vec base = toVec(p[p1], p[nx(p1)]);

        // the last condition makes sure that the cross products don't have the same sign
        while (p2 == p1 || p2 == nx(p1) || 
          sign(cross(base, toVec(p[p2], p[nx(p2)]))) == sign(cross(base, toVec(p[pv(p2)], p[p2])))) {
            // problematic if n == 2
          // sign(cross(base, p[nx(p2)] - p[p2])) == sign(cross(base, p[p2] - p[pv(p2)])))
            p2 = nx(p2);
        }

        if (vis[p1]) continue;
        vis[p1] = true;

        ans.push_back({p1, p2});
        ans.push_back({nx(p1), p2});

        // if both edges from p1 and p2 are parallel to each other
        if (cross(base, toVec(p[p2], p[nx(p2)])) == 0) {
          // p[nx(p2)] - p[p2]) == 0) {
            ans.push_back({p1, nx(p2)});
            ans.push_back({nx(p1), nx(p2)});
            vis[p2] = true;
        }
    }
    return ans;
}

int main() {
  int c;
  cin >> c;
  vector<point> pts(c);
  for (int i = 0; i < c; i++) {
      cin >> pts[i].x >> pts[i].y;    // [-1000, 1000]: can use double (and have good precision!)
  }
  vector<point> poly = CH_Andrew(pts);
  poly.pop_back();  // remove repeated point from polygon

  vector<ii> antipodal_points;
  if (poly.size() >= 3) {
    antipodal_points = all_anti_podal(poly);
  }
  else {
    // number of points <= 2
    antipodal_points = {{0, 1}};
  }

  double mx = DBL_MIN;
  for (auto &[p1, p2]: antipodal_points) {
    mx = max(mx, dist(poly[p1], poly[p2]));
  }
  cout << fixed << setprecision(10) << mx << endl;
  return 0;
}
