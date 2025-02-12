#include <bits/stdc++.h>
using namespace std;

struct point
{
    int64_t x, y;                                  // only used if more precision is needed
    point() { x = y = 0.0; }                      // default constructor
    point(int64_t _x, int64_t _y) : x(_x), y(_y) {} // user-defined
    bool operator<(const point &p) const
    {
        return x < p.x || (x == p.x && y < p.y);
    }
};

ostream &operator<<(ostream &os, const point &p)
{
    return os << "(" << p.x << ", " << p.y << ")";
}



struct vec
{
    int64_t x, y; // name: `vec' is different from STL vector
    vec(int64_t _x, int64_t _y) : x(_x), y(_y) {}
};
vec toVec(point a, point b)
{ // convert 2 points to vector a->b
    return vec(b.x - a.x, b.y - a.y);
}

int64_t cross(vec a, vec b) { return a.x * b.y - a.y * b.x; }

// note: to accept collinear points, we have to change the `> 0'
// returns true if point r is on the left side of line pq
bool ccw(point p, point q, point r)
{
    return cross(toVec(p, q), toVec(p, r)) > 0;
}



vector<point> CH_Andrew(vector<point> &Pts)
{ // overall O(n log n)
    int n = (int) Pts.size(), k = 0;
    vector<point> H(2 * n);
    sort(Pts.begin(), Pts.end()); // sort the points by x/y
    for (int i = 0; i < n; ++i)
    { // build lower hull
        while ((k >= 2) && !ccw(H[k - 2], H[k - 1], Pts[i]))
            --k;
        H[k++] = Pts[i];
    }
    H.resize(k);
    return H;
}

void solve()
{
    int n;
    cin >> n;
    vector<point> pts(n + 1);
    int64_t pref = 0;
    pts[0] = point(0, pref);
    for (int i = 1; i <= n; i++)
    {
        int ai;
        cin >> ai;
        pref += ai;
        pts[i] = point(i, pref);
    } 
    vector<point> lower_hull = CH_Andrew(pts);
    // for (point p: lower_hull) cout << p << endl;
    int sz = int(lower_hull.size());
    for (int i = 0; i < sz - 1; i++) {
        point p = lower_hull[i];
        point nxt = lower_hull[i + 1];
        int64_t cnt = nxt.x - p.x;
        double val = double(nxt.y - p.y) / double(cnt);
        for (int64_t j = p.x + 1; j <= nxt.x; j++) {
            cout << fixed << setprecision(10) << val << '\n';
        }
    }
}

int main()
{
    cin.tie(0)->ios::sync_with_stdio(0);
    solve();
    return 0;
}
