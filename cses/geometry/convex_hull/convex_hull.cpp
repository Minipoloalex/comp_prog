#include <bits/stdc++.h>
using namespace std;

struct P {
    int x, y;
    P operator-(const P &a) {
        return {x - a.x, y - a.y};
    }
    bool operator<(const P &o) const {
        return make_pair(this->x, this->y) < make_pair(o.x, o.y);
    }
};
int64_t operator*(const P &a, const P &b) {
    return (int64_t) a.x * b.y - (int64_t) a.y * b.x;
}
istream &operator>>(istream &iss, P &p) {
    return iss >> p.x >> p.y;
}
ostream &operator<<(ostream &oss, P &p) {
    return oss << "(" << p.x << ", " << p.y << ")";
}

vector<P> convex_hull(vector<P> &pts) {
    // assumes sorted by x
    // increasing x's -> top convex hull
    // decreasing x's -> bottom convex hull
    vector<P> ans;
    for (P &c: pts) {
        while (ans.size() >= 2) {
            P &a = ans.end()[-2];
            P &b = ans.end()[-1];
            bool c_on_left_of_b = (b - a) * (c - a) > 0;

            if (!c_on_left_of_b) break; // Do not remove b if value is <= 0 (collinear or on right)
            ans.pop_back();
        }
        ans.push_back(c);
    }
    return ans;
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int n;
    cin >> n;
    vector<P> pts(n);
    for (P &p: pts) cin >> p;

    // convex hull with top and bottom parts
    sort(pts.begin(), pts.end());
    vector<P> top = convex_hull(pts);
    reverse(pts.begin(), pts.end());
    vector<P> bottom = convex_hull(pts);

    cout << top.size() + bottom.size() - 2 << '\n';  // do not include the first and last point on the bottom hull
    for (P &p: top) {
        cout << p.x << " " << p.y << '\n';
    }
    // don't print repeated vertices
    for (int i = 1; i < int(bottom.size() - 1); i++) {
        cout << bottom[i].x << " " << bottom[i].y << '\n';
    }
    return 0;
}
