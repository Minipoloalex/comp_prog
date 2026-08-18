#include <bits/stdc++.h>
using namespace std;

#define sz(v) int(v.size())

// sign of x: -1, 0, +1.
// for doubles, use epsilon
template <class T>
int sgn(T x) { return (x > 0) - (x < 0); }

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
	// |this × p| = |this||p|sin(o) = 2 * parallelogram area (signed)
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

    Point<double> todouble() const {
        return Point<double>{x, y};
    }

	friend istream &operator>>(istream &is, P &p) {
		return is >> p.x >> p.y; }
	friend ostream &operator<<(ostream &os, P p) {
		return os << "(" << p.x << "," << p.y << ")"; }
};

typedef Point<long long> Pll;
typedef Point<double> Pd;

/*
Returns a vector of the points of the convex hull in CCW order.
Points on the edge of the hull between two other points are NOT considered part of the hull.
It handles "weird" hulls: when it is only one or two points
*/
vector<Pll> convexHull(vector<Pll> pts) {
	if (sz(pts) <= 1) return pts;
	sort(pts.begin(), pts.end());
	vector<Pll> h(sz(pts)+1);
	int s = 0, t = 0;
	// first the lower hull, then the upper hull
	for (int it = 2; it--; s = --t, reverse(pts.begin(), pts.end()))
		for (Pll p : pts) {
			while (t >= s + 2 && h[t-2].cross(h[t-1], p) <= 0) t--;
			h[t++] = p;
		}
	return {h.begin(), h.begin() + t - (t == 2 && h[0] == h[1])};
}

/**
These functions assume circles are defined by integer points and integer radii.
Hence the lack of EPS checks in some comparisons.
*/

/**
Finds the intersection between a circle and a line.
Returns a vector of either 0, 1, or 2 intersection points.
P is intended to be Point<double>
 */
vector<Pd> circleLine(Pd c, double r, Pd a, Pd b) {
	Pd ab = b - a, p = a + ab * (c-a).dot(ab) / ab.dist2();
	double s = a.cross(b, c), h2 = r*r - s*s / ab.dist2();
	if (h2 < 0) return {};
	if (h2 == 0) return {p};
	Pd h = ab.unit() * sqrt(h2);
	return {p - h, p + h};
}

const double PI = acos(-1);

void solve() {
    int n, r;
    cin >> n >> r;
    vector<Pll> pts(n);
    for (auto &p: pts) cin >> p;
    double ans = 0;
    vector<Pll> ch = convexHull(pts);
    if (ch.size() == 1) {
        ans = double(r)*r*PI / 2;
    }
    else {
        for (int i = 0; i < sz(ch); i++) {
            int nx = (i+1) % sz(ch);
            // intersect pts[i] and pts[nx] with the circle
            // get the angle total from that
            vector<Pd> ipts = circleLine(Pd{0, 0}, r, ch[i].todouble(), ch[nx].todouble());
            assert(sz(ipts) == 2);
            
            // may need to check which point is closest to i to disambiguate the order
            if ((ch[i].todouble() - ipts[0]).dist2() > (ch[nx].todouble() - ipts[0]).dist2()) {
                swap(ipts[0], ipts[1]);
            }
            double a1 = ipts[0].angle();
            double a2 = ipts[1].angle();
            if (a2 < a1) {
                a2 += PI + PI;
            }
            double adiff = a2 - a1;
            double sec = adiff*r*r;
            double tri = double(ipts[0].cross(ipts[1]));
            // cout << ch[i] << " " << ch[nx] << " " << ipts[0] << " " << ipts[1] << " ";
            // cout << " " << adiff << " " << sec << " " << tri << " ";
            // cout << endl;
            ans = max(ans, (sec - tri) / 2);
        }
    }
    ans = min(ans, double(r)*r*PI / 2); // best solution possible
    cout << fixed << setprecision(10);
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
