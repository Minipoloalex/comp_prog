#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int,int> ii;
#define nx(i) ((i)+1)%n
#define pv(i) ((i)-1+n)%n

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

struct vec { double x, y;
  vec(double _x, double _y) : x(_x), y(_y) {} };

vec toVec(point a, point b) {       // convert 2 points to vector a->b
  return vec(b.x-a.x, b.y-a.y); }

double cross(vec p1, vec p2) {
    return p1.x * p2.y - p1.y * p2.x;
}

// note: to accept collinear points, we have to change the `> 0'
// returns true if point r is on the left side of line pq
bool ccw(point p, point q, point r) {
  return cross(toVec(p, q), toVec(p, r)) > 0;
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

int sign(double num) {
    if (fabs(num) < EPS) return 0;
    else if (num < 0) return -1;
    else return 1;
}
double dist(point p1, point p2) {                // Euclidean distance
  // hypot(dx, dy) returns sqrt(dx*dx + dy*dy)
  return hypot(p1.x-p2.x, p1.y-p2.y);            // return double
}
point translate(const point &p, const vec &v) {  // translate p
  return point(p.x+v.x, p.y+v.y);                // according to v
}                                                // return a new point
vec scale(const vec &v, double s) {              // s = [<1..1..>1]
  return vec(v.x*s, v.y*s);                      // shorter/eq/longer
}  
double dot(vec a, vec b) { return (a.x*b.x + a.y*b.y); }

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

// Takes in a convex polygon where the last vertex is not repeated
// Note that the CH returns a repeated last vertex
// Returns all pairs of indices of antipodal pairs
// Only valid for p.size() >= 3;
// Does not handle points with precision problems (assumes integer coords)
// Modify other functions and structs (vec, toVec, cross, point) to support integer coords
double min_width(const vector<point> &p) {
  int n = (int) p.size();
  assert(n >= 3);

  int p1 = 0, p2 = 0; // two "pointers"
  double ans = DBL_MAX;

  // parallel edges should't be visited twice
  vector<bool> vis(n, false);

  auto handle = [&](int l1, int l2, int pt) {
    point proj;
    return distToLine(p[pt], p[l1], p[l2], proj);
  };

  for (;p1<n;p1++) {
    // the edge that we are going to consider in this iteration
    vec base = toVec(p[p1], p[nx(p1)]);

    // the last condition makes sure that the cross products don't have the same sign
    while (p2 == p1 || p2 == nx(p1) || 
      sign(cross(base, toVec(p[p2], p[nx(p2)]))) == sign(cross(base, toVec(p[pv(p2)], p[p2])))) {
        // problematic if n == 2
        p2 = nx(p2);
    }

    if (vis[p1]) continue;
    vis[p1] = true;

    ans = min(ans, handle(p1, nx(p1), p2));

    // ans.push_back({p1, p2});
    // ans.push_back({nx(p1), p2});

    // if both edges from p1 and p2 are parallel to each other
    if (cross(base, toVec(p[p2], p[nx(p2)])) == 0) {
        // ans.push_back({p1, nx(p2)});
        // ans.push_back({nx(p1), nx(p2)});
        vis[p2] = true;
    }
  }
  return ans;
}

double solve(int n) {
    vector<point> pts(n);
    for (auto &p: pts) {
        cin >> p.x >> p.y;
    }
    vector<point> CH = CH_Andrew(pts);
    CH.pop_back();

    double ans = min_width(CH);
    return ans;
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int n;
    int c = 1;
    while (cin >> n, n) {
        double ans = solve(n);
        cout << "Case " << c++ << ": " << fixed << setprecision(2) << ans + 0.005 << '\n';
    }

    return 0;
}
