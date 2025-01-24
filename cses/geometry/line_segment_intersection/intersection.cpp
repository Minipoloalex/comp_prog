#include <bits/stdc++.h>
using namespace std;

struct P {
    int x, y;
    P operator-(P &o) {
        return P{x - o.x, y - o.y};
    }
    int64_t operator*(const P &b) {
        return (int64_t) x * b.y - (int64_t) y * b.x;
    }
    int64_t triangle(P &a, P &b) {
        return (a - *this) * (b - *this);
    }
};

istream &operator>>(istream &iss, P &p) {
    return iss >> p.x >> p.y;
}

int sign(int64_t value) {
    return (value > 0) - (value < 0);
}

bool parallel(P &v1, P &v2) {
    return (v1 * v2) == 0;
}

bool collinear(P &p1, P &p2, P &p3, P &p4) {
    return p1.triangle(p2, p3) == 0 && p1.triangle(p2, p4) == 0;
}

bool bounding_box_collision(const P &p1, const P &p2, const P &p3, const P &p4) {
    if (min(p1.x, p2.x) > max(p3.x, p4.x) || min(p1.y, p2.y) > max(p3.y, p4.y)) {
        return false;
    }
    // could have used swap here (and after to ensure points remain same) instead of copy pasting
    if (min(p3.x, p4.x) > max(p1.x, p2.x) || (min(p3.y, p4.y) > max(p1.y, p2.y))) {
        return false;
    }
    return true;
}

bool intersect(array<P, 4> &p) {
    P v1 = p[1] - p[0];
    P v2 = p[3] - p[2];
    if (parallel(v1, v2)) {
        if (collinear(p[0], p[1], p[2], p[3]) && bounding_box_collision(p[0], p[1], p[2], p[3])) {
            return true;
        }
        return false;
    }

    auto equal_signs = [&](P &p1, P &p2, P &o1, P &o2) -> bool {
        // tells us if segment (o1, o2) is completely on one side of segment (p1, p2)
        // may need to be careful if sign = 0
        return sign(p1.triangle(p2, o1)) == sign(p1.triangle(p2, o2));
    };

    if (equal_signs(p[0], p[1], p[2], p[3]) || equal_signs(p[2], p[3], p[0], p[1])) {
        return false;
    }
    return true;
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        array<P, 4> pts;
        for (P &p: pts) {
            cin >> p;
        }
        cout << (intersect(pts) ? "YES" : "NO") << '\n';
    }
    return 0;
}
