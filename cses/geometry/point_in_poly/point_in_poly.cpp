#include <bits/stdc++.h>
using namespace std;

struct P {
    int x, y;
    P operator-(const P &o) const {
        return {x - o.x, y - o.y};
    }
    int64_t operator*(const P& o) const {
        return (int64_t) x * o.y - (int64_t) y * o.x;
    }
    friend istream& operator>>(istream &iss, P &p) {
        return iss >> p.x >> p.y;
    }
    int64_t triangle(P &p1, P &p2) {
        P &p = *this;
        return (p1 - p) * (p2 - p);
    }
};

bool on_segment(P &p, P &p1, P &p2) {
    // small x, big x, small y, big y
    int sx = min(p1.x, p2.x);
    int bx = max(p1.x, p2.x);
    int sy = min(p1.y, p2.y);
    int by = max(p1.y, p2.y);
    // collinear and in bounding box
    return p1.triangle(p2, p) == 0 && (
        sx <= p.x && p.x <= bx &&
        sy <= p.y && p.y <= by
    );
}

int point_in_poly(P &p, vector<P> &poly) {
    int n = int(poly.size());
    bool on_boundary = false;
    int intersects = 0;
    for (int i = 0; i < n; i++) {
        P &p1 = poly[i];
        int j = i + 1 == n ? 0 : i + 1;
        P &p2 = poly[j];
        if (on_segment(p, p1, p2)) {
            on_boundary = true;
            break;
        }
        // Implemented with approximately vertical ray, tilted to the right: (p.x, p.y) -> (p.x + 1, infinite y)
        // Slightly tilted to the right, so: <= is left, > is right (nothing is collinear -> that's the objective)
        if (p1.x <= p.x && p.x < p2.x && p1.triangle(p2, p) < 0) {
                // p1 p p2
            intersects++;
        }
        else if (p2.x <= p.x && p.x < p1.x && p2.triangle(p1, p) < 0) {
            // p2 p p1
            intersects++;
        }
    }
    if (on_boundary) return 0;          // on boundary
    if (intersects % 2 == 0) return -1; // outside
    return 1;                          // inside
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<P> poly(n);
    for (auto &pt: poly) cin >> pt;
    while (m--) {
        P p;
        cin >> p;
        int res = point_in_poly(p, poly);
        string ans;
        if (res == 0) {
            ans = "BOUNDARY";
        }
        else if (res == 1) ans = "INSIDE";
        else if (res == -1) ans = "OUTSIDE";

        cout << ans << '\n';
    }
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    solve();
    return 0;
}
