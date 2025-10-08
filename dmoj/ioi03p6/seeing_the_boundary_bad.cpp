#include <bits/stdc++.h>
using namespace std;

// WAs a lot (deals with doubles)

const double EPS = 1e-9;

struct P {
    int x, y;
    P operator-(const P &o) const {
        return P{x-o.x, y-o.y};
    }
};

int64_t cross(P a, P b) {
    return (int64_t) a.x * b.y - (int64_t) a.y * b.x;
}
istream &operator>>(istream &iss, P &p) {
    return iss >> p.x >> p.y;
}

const double PI = acos(-1);

void solve() {
    int n, r;
    cin >> n >> r;
    P loc;
    cin >> loc;
    auto to_ang = [&](int x, int y) {
        return atan2(y - loc.y, x - loc.x) + PI;
    };
    vector<pair<double, int>> events;
    events.reserve(2 * r + 4 * n);
    for (int i = 0; i < r; i++) {
        double small = DBL_MAX, big = DBL_MIN;  // usually entrance < exit, but edge case!
        P vs, vb;
        int pi;
        cin >> pi;
        while (pi--) {
            P p;
            cin >> p;
            double ang = to_ang(p.x, p.y);
            if (ang < small) {
                small = ang;
                vs = p;
            }
            if (ang > big) {
                big = ang;
                vb = p;
            }
        }
        if (cross(vs - loc, vb - loc) < 0) {    // don't need to consider == 0
            swap(small, big);
        };
        events.emplace_back(small, 0);  // entrance
        events.emplace_back(big, 2);    // exit
    }

    for (int x = 0; x <= n; x++) {
        int y;
        y = 0;
        events.emplace_back(to_ang(x, y), 1);
        y = n;
        events.emplace_back(to_ang(x, y), 1);
    }
    for (int y = 1; y < n; y++) {
        int x;
        x = 0;
        events.emplace_back(to_ang(x, y), 1);
        x = n;
        events.emplace_back(to_ang(x, y), 1);
    }
    sort(events.begin(), events.end(), [&](const pair<double,int> &a, const pair<double,int>&b) {
        if (fabs(a.first - b.first) > EPS) {
            return a.first < b.first;
        }
        return a.second < b.second;
    });
    int block = 0, ans = 0;
    for (auto &[ang, type]: events) {
        if (type == 1) {
            if (block == 0) ans++;
        }
        else if (type == 2) {
            if (block == 0) ans = 0;
            else block--;
        }
        else if (type == 0) {
            block++;
        }
    }
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    solve();
    return 0;
}
