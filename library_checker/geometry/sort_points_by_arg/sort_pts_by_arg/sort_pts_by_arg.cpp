#include <bits/stdc++.h>
using namespace std;

struct P {
    int x, y;
    friend istream &operator>>(istream &iss, P &p) {
        return iss >> p.x >> p.y;
    }
};

double angle(P &p) {
    return atan2(p.y, p.x);
}

void solve() {
    int n;
    cin >> n;
    vector<P> pts(n);
    for (auto &p: pts) {
        cin >> p;
    }

    sort(pts.begin(), pts.end(), [](P &a, P &b) {
        return angle(a) < angle(b);
    });
    for (auto &p: pts) {
        cout << p.x << " " << p.y << '\n';
    }
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    solve();
    return 0;
}
