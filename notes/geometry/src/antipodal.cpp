#include <bits/stdc++.h>
using namespace std;

// Anti-podal points: can be adapted for several rotating caliper problems
// Basic geometry based on CP4 Book
// Anti-podal points based on https://codeforces.com/blog/entry/133763

typedef long long ll;
typedef pair<int,int> ii;
#define nx(i) ((i)+1)%n
#define pv(i) ((i)-1+n)%n

struct point {
  ll x, y;
  bool operator <(const point &p) const {
    return x < p.x || (x == p.x && y < p.y);
  }
};

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
  int n = Pts.size(), k = 0;
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
vector<ii> all_antipodal(const vector<point> &p) {
  int n = (int) p.size();
  assert(n >= 3);

  int p1 = 0, p2 = 0; // two "pointers"
  vector<ii> ans;

  // parallel edges should't be visited twice
  vector<bool> vis(n, false);

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

    ans.push_back({p1, p2});
    ans.push_back({nx(p1), p2});

    // if both edges from p1 and p2 are parallel to each other
    if (cross(base, toVec(p[p2], p[nx(p2)])) == 0) {
        ans.push_back({p1, nx(p2)});
        ans.push_back({nx(p1), nx(p2)});
        vis[p2] = true;
    }
  }
  return ans;
}
