#include <bits/stdc++.h>
using namespace std;

using vi = vector<int64_t>;
using vvi = vector<vi>;

const long long INF = (long long)1e18;
const int64_t MAX_SUM = int64_t(3e12);
using i128 = __int128_t;

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
typedef Point<double> Pd;

static inline i128 cross128(const Pll& u, const Pll& v) {
    return (i128)u.x * v.y - (i128)u.y * v.x;
}

template<bool SLOPES_INC, bool QUERIES_INC>
struct monotonic_dp_hull_max {
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
        while (size() >= 2) {
            Pll u = points.back() - q;
            Point v = points[size() - 2] - points.back();
            if (cross128(u, v) > 0) break;
            points.pop_back();  // if >= 0
        }
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

        // Maybe should also switch to cross128 for answering queries
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
struct monotonic_dp_hull_min {
    // After (m,b) -> (-m,-b), slopes order flips, queries order stays the same
    using Max = monotonic_dp_hull_max<!SLOPES_INC, QUERIES_INC>;
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
    // Not sure if this solution could be hacked or not

    int n, k;
    cin >> n >> k;
    vector<int64_t> c(n + 1);
    for (int i = 1; i <= n; i++) cin >> c[i];
    vi s(n + 1), p(n + 1), t(n + 1);
    for (int i = 1; i <= n; i++) {
        s[i] = s[i - 1] + (n - i + 1) * c[i];
        p[i] = p[i - 1] + i * c[i];
        t[i] = t[i - 1] + c[i];
    }
    vvi yes(k + 1, vi(n + 1, INF)), no(k + 1, vi(n + 1, INF));
    yes[0][0] = 0;  // min cost to place a school here (with k schools and children up to house i)
    no[0][0] = 0;   // min cost to make all children go left of i (with k schools and children up to house i)

    monotonic_dp_hull_min<false,true> cht1; // min, increasing queries, decreasing slopes
    monotonic_dp_hull_min<false,true> cht2; // min, increasing queries, decreasing slopes
    for (int ki = 1; ki <= k; ki++) {
        cht1.add(0, 0);
        for (int i = 1; i <= n; i++) {
            yes[ki][i] = cht1.query(i) + s[i-1] - n * t[i-1] + i * t[i-1] - t[i-1];
            cht2.add(-i, yes[ki][i] - p[i] + i * t[i]);

            no[ki][i] = cht2.query(t[i]) + p[i];
            cht1.add(-t[i], no[ki-1][i] - s[i] + n * t[i] + t[i]);
        }
        cht1.clear();
        cht2.clear();
    }
    int64_t ans = no[k][n];
    cout << ans << '\n';
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
