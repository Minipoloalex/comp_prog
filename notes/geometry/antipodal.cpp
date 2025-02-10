#include <bits/stdc++.h>
using namespace std;

// Minimalistic anti-podal points
// Basic geometry based on CP4 Book
// Anti-podal points based on https://codeforces.com/blog/entry/133763

typedef long long ll;
typedef pair<int,int> ii;
#define nx(i) ((i)+1)%n
#define pv(i) ((i)-1+n)%n

struct point {
    ll x, y;
};

struct vec { ll x, y;
  vec(ll _x, ll _y) : x(_x), y(_y) {} };

vec toVec(point a, point b) {       // convert 2 points to vector a->b
  return vec(b.x-a.x, b.y-a.y); }

ll cross(vec p1, vec p2) {
    return p1.x * p2.y - p1.y * p2.x;
}

int sign(ll num) {
    if (num < 0) return -1;
    else if (num == 0) return 0;
    else return 1;
}

// Takes in a convex polygon where the last vertex is not repeated
// Note that the CH returns a repeated last vertex
// Returns all pairs of indices of antipodal pairs
// Only valid for p.size() >= 3;
// Does not handle points with precision problems (assumes integer coords)
// Modify other functions and structs (vec, toVec, cross, point) to support integer coords
vector<ii> all_anti_podal(const vector<point> &p) {
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
