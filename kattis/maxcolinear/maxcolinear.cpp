#include <bits/stdc++.h>
using namespace std;
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
inline bool operator==(const Angle &a, const Angle &b) {
    return make_tuple(a.t, a.half(), a.y * (int64_t)b.x)
         == make_tuple(b.t, b.half(), a.x * (int64_t)b.y);
}

// do not use cross
using P = Point<int>;
#define sz(v) int((v).size())

bool solve() {
    int n;
    cin >> n;
    if (n == 0) return false;
    vector<P> pts(n);
    for (auto &pt: pts) cin >> pt;
    int ans = 1;
    for (int i = 0; i < n; i++) {
        vector<Angle> angles;
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            P vec = pts[j] - pts[i];
            angles.emplace_back(vec.x, vec.y);
        }
        sort(angles.begin(), angles.end());
        int angSZ = sz(angles);
        for (int j = 0; j < angSZ; j++) {
            angles.push_back(angles[j].t360());
        }
        int mx = 0;
        int ptr = 0;

        // It's not true that mx will be the max of this point (for example, if we wanted some kind of sum, this would be incorrect)
        // But at least one of the points of the same "chain" will give the optimal result
        for (int j = 0; j < angSZ; j++) {
            while (angles[ptr] < angles[j].t180()) {
                ptr++;
            }
            int start = ptr;
            while (angles[ptr] == angles[j].t180()) {
                ptr++;
            }
            int end = ptr;
            mx = max(mx, end - start);
        }
        if (angSZ > 0) {
            ans = max(ans, mx + 2);
        }
    }
    cout << ans << '\n';
    return true;
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    // int t = 1;
    // cin >> t;
    while (solve()) {}
    return 0;
}
