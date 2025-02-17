#include <bits/stdc++.h>
using namespace std;

struct point {
    int x, y;
    point() { x = y = 0.0; }                      // default constructor
    point(int _x, int _y) : x(_x), y(_y) {}        // user-defined
    bool operator <(const point &p) const {
     return x < p.x || (x == p.x && y < p.y);
    }
};
struct vec { int x, y;  // name: `vec' is different from STL vector
    vec(int _x, int _y) : x(_x), y(_y) {} };
  
  vec toVec(point a, point b) {       // convert 2 points to vector a->b
    return vec(b.x-a.x, b.y-a.y);
}
  
int64_t cross(vec a, vec b) { return (int64_t) a.x*b.y - (int64_t) a.y*b.x; }

// note: to accept collinear points, we have to change the `> 0'
// returns true if point r is on the left side of line pq
bool ccw(point p, point q, point r) {
    return cross(toVec(p, q), toVec(p, r)) > 0;
  }

vector<point> CH_Andrew(vector<point> &Pts) {    // overall O(n log n)
    int n = (int) Pts.size(), k = 0;
    vector<point> H(2*n);
    sort(Pts.begin(), Pts.end());                  // sort the points by x/y

    for (int i = 0; i < n; ++i) {                  // build lower hull -> now upper hull
      while ((k >= 2) && ccw(H[k-2], H[k-1], Pts[i])) --k;
      H[k++] = Pts[i];
    }
    // for (int i = n-2, t = k+1; i >= 0; --i) {       // build upper hull
    //   while ((k >= t) && !ccw(H[k-2], H[k-1], Pts[i])) --k;
    //   H[k++] = Pts[i];
    // }
    H.resize(k);
    return H;
  }
void solve() {
    int n;
    cin >> n;
    vector<point> pts(n + 2);
    pts[0] = point(0, 0);
    for (int i = 1; i <= n; i++) {
        int fi;
        cin >> fi;
        pts[i] = point(i, fi);
    }
    pts[n + 1] = point(n + 1, 0);

    vector<point> ch = CH_Andrew(pts);
    for (int i = 0; i < int(ch.size() - 1); i++) {
        int j = i + 1;
        int64_t yd = ch[j].y - ch[i].y;
        int64_t total_xd = ch[j].x - ch[i].x;
        for (int x = ch[i].x; x < ch[j].x; x++) {
            if (x >= 1 && x <= n) {
                int64_t xd = x - ch[i].x;

                // safer with 128 bits intermediate calculation
                // __int128 numerator = ( (__int128)ch[i].y * total_xd + (__int128)yd * xd ) * 100'000LL;
                // int64_t ans = (int64_t)(numerator / total_xd);

                // limit for intermediate calculations is a little over 1e19 (fits in uint64_t)
                uint64_t ans = uint64_t(int64_t(ch[i].y) * total_xd + (yd * xd)) * 100'000ULL / total_xd;

                cout << ans << '\n';
            }
        }
    }
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    // freopen("balance.in", "r", stdin);
    // freopen("balance.out", "w", stdout);
    solve();
    return 0;
}
