#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

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
};

/**
 * Angle as an int vector (x,y) + a lap counter t (how many full CCW turns).
 * Used for rotational sweeping / ordering directions continuously across 2π.
 */
struct Angle {
    int x, y; // direction from origin
    int t;    // number of full turns (2π) already passed
    Angle(Point<ll> p): x(int(p.x)), y(int(p.y)), t(0) {}
    Angle(int _x, int _y, int _t=0) : x(_x), y(_y), t(_t) {}

    Angle operator-(const Angle &b) const { return {x - b.x, y - b.y, t}; }

    // 1 if in lower half-plane (y<0) or on negative x-axis (y==0 && x<0); else 0.
    // Splits circle at the negative x-axis so sorting doesn't jump at π/-π.
    int half() const {
        assert(x || y);
        return y < 0 || (y == 0 && x < 0);
    }

    // Rotate +90° (CCW).
    // The wrap happens when starting in lower half and on the right side (x>=0).
    Angle t90() const { return {-y, x, t + (half() && x >= 0)}; }

    // Rotate +180°. Crossing the boundary iff we started in the lower half.
    Angle t180() const { return {-x, -y, t + half()}; }

    // Same direction, next lap (t+1).
    Angle t360() const { return {x, y, t + 1}; }
};

// Angular order: first by t (earlier laps), then by half (upper before lower),
// then by orientation (a<b iff a is CCW from b).
// Add a.dist2()/b.dist2() if you also want to break ties by length.
inline bool operator<(const Angle &a, const Angle &b) {
    return make_tuple(a.t, a.half(), a.y * (int64_t)b.x)
         < make_tuple(b.t, b.half(), a.x * (int64_t)b.y);
}

void solve() {
    int n, r;
    cin >> n >> r;
    Point<ll> c; cin >> c;
    if (c.x == 0 || c.x == n || c.y == 0 || c.y == n) while(1);

    // could have used the same vector, but this spends less memory (limit of 64MB)
    vector<pair<Angle,int>> events; events.reserve(4*n+2*r + 10);

    // point, type (enter or exit), rock id
    vector<tuple<Angle, int, int>> angles; angles.reserve(2*r + 10);
    Point<ll> fst, lst;
    for (int i = 0; i < r; i++) {   // rocks are convex polygons
        int pi; cin >> pi;
        for (int j = 0; j < pi; j++) {
            Point<ll> pt; cin >> pt;
            if (j == 0) { fst = pt; lst = pt; }
            else {
                if (c.cross(pt, fst) > 0) {
                    fst = pt;
                }
                if (c.cross(pt, lst) < 0) {
                    lst = pt;
                }
            }
        }
        if (fst == c || lst == c) while(1);
        angles.emplace_back(fst - c, 0, i);    // first all rocks should enter, before they all exit
        angles.emplace_back(lst - c, 2, i);    // also, before they exit, we should go through the fences

        events.emplace_back(fst - c, 0);
        events.emplace_back(lst - c, 2);
    }
    sort(angles.begin(), angles.end());
    int cur = 0;
    vector<bool> active(r);
    for (auto &[p, type, rockid]: angles) { // to setup the starting value of cur
        if (type == 0) {
            cur++;
            active[rockid] = true;
        }
        else if (type == 2 && active[rockid]) {
            cur--;
            active[rockid] = false;
        }
    }
    
    // could have avoided placing the fence post events by doing
    // something similar to the last part of https://usaco.guide/plat/sweep-line#implementation-5
    // basically, use a next_fence_post function and go through posts until reaching the next event
    // and it's easy to compare the fence post and the next event with this angle class
    events.emplace_back(Point<ll>(0,0)-c,1);
    events.emplace_back(Point<ll>(n,0)-c,1);
    events.emplace_back(Point<ll>(0,n)-c,1);
    events.emplace_back(Point<ll>(n,n)-c,1);
    for (int i = 1; i < n; i++) {
        events.emplace_back(Point<ll>(0, i)-c,1);    // 0, [1,n-1]
        events.emplace_back(Point<ll>(i, 0)-c,1);    // [1,n-1], 0
        events.emplace_back(Point<ll>(n, i)-c,1);    // n, [1,n-1]
        events.emplace_back(Point<ll>(i, n)-c,1);    // [1,n-1], n
    }
    sort(events.begin(), events.end());
    int ans = 0;
    for (auto &[p, type]: events) {
        if (type == 0) {
            cur++;
        }
        else if (type == 1) {
            if (cur == 0) ans++;
        }
        else if (type == 2) {
            cur--;
        }
    }
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    solve();
    return 0;
}
