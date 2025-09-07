#include <bits/stdc++.h>
using namespace std;

template <class T>
int sgn(T x) { return (x > 0) - (x < 0); }

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

void solve() {
    int n;
    cin >> n;
    vector<pair<int,int>> pts(n);
    for (auto &[x, y]: pts) cin >> x >> y;

    vector<Pd> curpts(n);
    auto set = [&](Pd dest) {
        // Project each point to the axis defined by
        // (0,0) -> (dest.x, dest.y)
        for (int i = 0; i < n; i++) {
            Pd cur(pts[i].first, pts[i].second);
            double projX = dest.perp().unit().dot(cur);
            double projY = dest.unit().dot(cur);
            curpts[i] = Pd(projX, projY);
        }
    };
    auto dist = [&](int i, int j) -> double {
        auto &[x1, y1] = curpts[i];
        auto &[x2, y2] = curpts[j];
        return fabs(x1 - x2) + fabs(y1 - y2);
    };

    vector<vector<double>> dp;
    function<double(int,int)> tsp = [&](int mask, int cur) -> double {
        if (mask == (1 << n) - 1) {
            return 0;
        }
        double &ans = dp[mask][cur];
        if (fabs(ans+1) > 0.1) return ans;

        double res = DBL_MAX;
        for (int i = 0; i < n; i++) {
            if (((1 << i) & mask) == 0) {
                res = min(res, dist(cur, i) + tsp(mask | (1 << i), i));
            }
        }
        return ans = res;
    };
    double ans = DBL_MAX;
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            int dx = pts[j].first - pts[i].first;
            int dy = pts[j].second - pts[i].second;
            Pd dest(dx, dy);
            set(dest);
            // cout << "set: " << i << " " << j << endl;
            dp.assign(1 << n, vector<double>(n, -1));
            for (int k = 0; k < n; k++) {
                ans = min(ans, tsp(1 << k, k));
            }
        }
    }
    cout << fixed << setprecision(10) << ans << '\n';
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
