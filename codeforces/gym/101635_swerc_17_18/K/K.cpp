#include <bits/stdc++.h>
using namespace std;

// Anti-podal points: can be adapted for several rotating caliper problems
// Basic geometry based on CP4 Book
// Anti-podal points based on https://codeforces.com/blog/entry/133763

typedef long long ll;
typedef pair<int,int> ii;
#define nx(i) ((i)+1)%N
#define pv(i) ((i)-1+N)%N
/**
 * Class to handle points in the plane.
 * T can be double or long long. Avoid int because of overflow.
 * 
 * To use double, you should adapt comparisons with an epsilon.
 */
template<class T>
struct Point {
	typedef Point P;
	T x, y;
	explicit Point(T _x=0, T _y=0) : x(_x), y(_y) {}

	// for doubles, use epsilon
	bool operator<(P p) const { return tie(x,y) < tie(p.x,p.y); }
	bool operator==(P p) const { return tie(x,y)==tie(p.x,p.y); }

	P operator+(P p) const { return P(x+p.x, y+p.y); }
	P operator-(P p) const { return P(x-p.x, y-p.y); }
	P operator*(T d) const { return P(x*d, y*d); }
	P operator/(T d) const { return P(x/d, y/d); }

	T dot(P p) const { return x*p.x + y*p.y; }

	// this × p (both vectors)
	// >0 if p is CCW (left) from this, <0 if CW (right), 0 if collinear
	// |this × p| = |this||p|sinθ = 2 * parallelogram area (signed)
	T cross(P p) const { return x*p.y - y*p.x; }

	// (a - this) × (b - this) = 2 * signed triangle area (this, a, b)
	T cross(P a, P b) const { return (a-*this).cross(b-*this); }

	T dist2() const { return x*x + y*y; }
	double dist() const { return sqrt((double)dist2()); }

	// angle to x-axis in interval [-pi, pi]
	double angle() const { return atan2(y, x); }

	// unit vector (dist()=1). Division by 0 if zero vector
    // For int T, truncates: only use for floating types.
	P unit() const { return *this/dist(); }

	P perp() const { return P(-y, x); } // rotates +90 degrees (CCW)
	P normal() const { return perp().unit(); }

	// returns point rotated 'a' radians ccw around the origin
	P rotate(double a) const {
		return P(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a)); }

	friend istream &operator>>(istream &is, P &p) {
		return is >> p.x >> p.y; }
	friend ostream &operator<<(ostream &os, P p) {
		return os << "(" << p.x << "," << p.y << ")"; }

    Point<double> todouble() const {
        return Point<double>(double(x), double(y));
    }
};

typedef Point<double> P;
typedef Point<ll> point;

// Returns the shortest distance between point p and the line segment from point s to e.
double segdist(P const& s, P const& e, P const& p) {
	if (s==e) return (p-s).dist();
	auto d = (e-s).dist2(), t = min(d,max(.0,(p-s).dot(e-s)));
	return ((p-s)*d-(e-s)*t).dist()/d;
}

double pdist(point &a, point &b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

struct vec { ll x, y;
  vec(ll _x, ll _y) : x(_x), y(_y) {} };

vec toVec(point a, point b) {       // convert 2 points to vector a->b
  return vec(b.x-a.x, b.y-a.y); }

ll cross(vec p1, vec p2) {
    return p1.x * p2.y - p1.y * p2.x;
}

// note: to accept collinear points, we have to change the `> 0'
// returns true if point r is on the left side of line pq
bool ccw(point p, point q, point r) {
  return cross(toVec(p, q), toVec(p, r)) > 0;
}

vector<point> CH_Andrew(vector<point> &Pts) {    // overall O(n log n)
  int n = int(Pts.size()), k = 0;
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
// Note that our CH implementations return a repeated last vertex
// Assumes no 3 collinear points
// Returns all pairs of indices of antipodal pairs
// Only valid for p.size() >= 3;
// Does not handle points with precision problems (assumes integer coords)
// Modify other functions and structs (vec, toVec, cross, point) to support integer coords
vector<ii> all_anti_podal(const vector<point> &p) {
  int N = (int) p.size();
  assert(N >= 3);

  int p1 = 0, p2 = 0; // two "pointers"
  vector<ii> ans;

  // parallel edges should't be visited twice
  vector<bool> vis(N, false);

  for (;p1<N;p1++) {
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

    ans.push_back({p1, p2});
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

void solve() {
    int n;
    cin >> n;
    int64_t r;
    cin >> r;
    vector<point> pts(n);
    for (auto &p: pts) cin >> p.x >> p.y;
    vector<point> ch = CH_Andrew(pts);
    ch.pop_back();
    if (ch.size() <= 2) {
        cout << "0\n";
        return;
    }
    vector<ii> antipodal = all_anti_podal(ch);
    int N = (int)ch.size();
    double mn = DBL_MAX;
    for (auto &[i, j]: antipodal) {
        mn = min(mn, segdist(ch[i].todouble(), ch[nx(i)].todouble(), ch[j].todouble()));
    }
    cout << fixed << setprecision(15);
    cout << mn << '\n';
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
