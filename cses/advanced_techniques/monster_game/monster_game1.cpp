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

typedef Point<long long> Pll;

template<bool SLOPES_INC, bool QUERIES_INC>
struct monotonic_dp_hull_max_unified {
    // Internally we make slopes nondecreasing by flipping sign if needed.
    static constexpr long long S = SLOPES_INC ? 1 : -1;

    // After x -> S*x, the internal query direction is:
    //   - same as external when S == +1
    //   - flipped when S == -1
    static constexpr bool QINC_INTERNAL = (QUERIES_INC == SLOPES_INC);

    long long prev_X = LLONG_MIN, prev_Y = 1;
    deque<Pll> points;

    void add(const Pll &p) {
        Pll q{S * p.x, p.y};                      // flip slopes if needed
        assert(points.empty() || q.x >= points.back().x);

        if (!points.empty() && q.x == points.back().x) {
            if (q.y <= points.back().y) return;   // keep larger b for max hull
            points.pop_back();
        }
        while (size() >= 2 &&
               ((points.back() - q).cross(points[size() - 2] - points.back())) <= 0)
            points.pop_back();
        points.push_back(q);
    }
    void add(long long m, long long b) { add(Pll{m, b}); }

    long long query(long long x, long long y = 1) {
        assert(!points.empty());
        long long X = S * x;                      // match slope flip to preserve mx + by

        if (prev_X != LLONG_MIN) {
            if (QINC_INTERNAL)  assert(X * prev_Y >= prev_X * y); // nondecreasing
            else                assert(X * prev_Y <= prev_X * y); // nonincreasing
        }
        prev_X = X; prev_Y = y;

        if (QINC_INTERNAL) {
            // pop from front when queries are nondecreasing
            while (size() >= 2 &&
                   X * (points[1].x - points[0].x) >= (points[0].y - points[1].y) * y)
                points.pop_front();
            return points[0].x * X + points[0].y * y;
        } else {
            // pop from back when queries are nonincreasing
            while (size() >= 2 &&
                   X * (points[size() - 2].x - points.back().x) >=
                   (points.back().y - points[size() - 2].y) * y)
                points.pop_back();
            return points.back().x * X + points.back().y * y;
        }
    }

    void clear() { points.clear(); prev_X = LLONG_MIN; prev_Y = 1; }
    int size() const { return (int)points.size(); }
};

/*
Min hull via sign flip, compatible with any monotonicities.
SLOPES_INC/QUERIES_INC describe the ORIGINAL data passed in.
*/
template<bool SLOPES_INC, bool QUERIES_INC>
struct monotonic_dp_hull_min_unified {
    // After (m,b) -> (-m,-b), slopes order flips, queries order stays the same
    using Max = monotonic_dp_hull_max_unified<!SLOPES_INC, QUERIES_INC>;
    Max hull;

    // Add a line y = m*k + b  (store as (-m, -b) to turn min into max)
    void add(long long m, long long b) { hull.add(-m, -b); }

    // Query the minimum of m*x + b*y for monotone nondecreasing x/y
    long long query(long long x, long long y = 1) {
        return -hull.query(x, y);
    }

    void clear() { hull.clear(); }
    int size() const { return hull.size(); }
};

void solve() {
    int n, x;
    cin >> n >> x;
    vector<int> f(n + 1), s(n + 1);
    f[0] = x;
    for (int i = 1; i <= n; i++) cin >> s[i];
    for (int i = 1; i <= n; i++) cin >> f[i];
    monotonic_dp_hull_min_unified<false,true> hull;

    vector<int64_t> dp(n + 1);
    hull.add(f[0], dp[0]);
    for (int i = 1; i <= n; i++) {
        dp[i] = hull.query(s[i]);
        hull.add(f[i], dp[i]);
    }
    cout << dp[n] << '\n';
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
