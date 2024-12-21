#include <bits/stdc++.h>
using namespace std;

struct P {
    int x, y;
    P operator-(const P &o) const {
        return P{x - o.x, y - o.y};
    }
};

int64_t operator*(const P &a, const P &b) {
    return (int64_t) a.x * b.y - (int64_t) a.y * b.x;
}

istream& operator>>(istream &in, P& p) {
    return in >> p.x >> p.y;
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int n;
    cin >> n;
    vector<P> pts(n);
    for (P &p: pts) {
        cin >> p;
    }
    int64_t area_2 = 0;
    for (int i = 0; i < n; i++) {
        int j = (i + 1) == n ? 0: i + 1;
        area_2 += pts[i] * pts[j];
    }
    cout << abs(area_2) << '\n';
    return 0;
}
