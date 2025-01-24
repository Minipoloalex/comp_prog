#include <bits/stdc++.h>
using namespace std;

struct P {
    int x, y;
    friend istream &operator>>(istream &iss, P &p) {
        return iss >> p.x >> p.y;
    }
    int64_t operator*(const P &o) {
        return (int64_t) x * o.y - (int64_t) y * o.x;
    }
    P operator-(const P &o) const {
        return {x - o.x, y - o.y};
    }
};

int64_t double_area(vector<P> &poly) {
    int n = int(poly.size());
    int64_t ans = 0;
    for (int i = 0; i < n; i++) {
        int j = i + 1 < n ? i + 1 : 0;
        ans += poly[i] * poly[j];
    }
    return abs(ans);
}

int64_t boundary_lattice_points(vector<P> &poly) {
    int n = int(poly.size());
    int64_t ans = 0;
    for (int i = 0; i < n; i++) {
        int j = i + 1 < n ? i + 1 : 0;
        P &p1 = poly[i], &p2 = poly[j];
        int segx = abs(p1.x - p2.x);
        int segy = abs(p1.y - p2.y);
        ans += gcd(segx, segy);
        // no need for +1 or -1
        // we count vertex i and others if they exist
    }
    return ans;
}

void solve() {
    int n;
    cin >> n;
    vector<P> poly(n);
    for (auto &pt: poly) cin >> pt;
    int64_t two_area = double_area(poly);
    int64_t boundary_pts = boundary_lattice_points(poly);

    // Subtracting to area ensures it is divisible by 2
    int64_t inside_pts = (two_area - boundary_pts) / 2 + 1;
    cout << inside_pts << " " << boundary_pts << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    solve();
    return 0;
}
