#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct point {
    ll x, y;
    point() { x = y = 0; } 
    point(ll _x, ll _y): x(_x), y(_y) {}

    bool operator<(point o) const {
        // by x-coordinate. if tie, by y
        return x < o.x || (x == o.x && y < o.y);
    }
    point operator-(point o) const {
        return {x - o.x, y - o.y};
    }
    point operator+(point o) const {
        return {x + o.x, y + o.y};
    }
    ll dist2() const { return x*x + y*y; }
};

// from KATCL: https://github.com/kth-competitive-programming/kactl/blob/main/content/geometry/ClosestPair.h
pair<point, point> closest(vector<point> v) {
    // operator< compares by x, and if tie, by y
    assert(v.size() > 1);
    set<point> S;
    sort(v.begin(), v.end(), [](point a, point b) { return a.y < b.y; });
    pair<ll, pair<point,point>> ret{LLONG_MAX, {point(), point()}};
    int j = 0;
    for (point p : v) {
        point d{1 + (ll)sqrt(ret.first), 0};
        while (v[j].y <= p.y - d.x) S.erase(v[j++]);
        auto lo = S.lower_bound(p - d), hi = S.upper_bound(p + d);
        for (; lo != hi; ++lo)
            ret = min(ret, {(*lo - p).dist2(), {*lo, p}});
        S.insert(p);
    }
    return ret.second;
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int n;
    cin >> n;
    vector<point> v(n);
    for (auto &p: v) {
        cin >> p.x >> p.y;
    }
    pair<point,point> p = closest(v);
    cout << (p.first - p.second).dist2() << endl;
    return 0;
}
