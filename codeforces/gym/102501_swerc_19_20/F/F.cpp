#include <bits/stdc++.h>
using namespace std;

struct point {
    int64_t x, y;
};

int64_t area(const vector<point> &P) {
  int64_t ans = 0.0;
  for (int i = 0; i < (int)P.size()-1; ++i)      // Shoelace formula
    ans += (P[i].x*P[i+1].y - P[i+1].x*P[i].y);
  return abs(ans);   // 2*area
}

void solve() {
    int n;
    cin >> n;
    int64_t ans = 0;
    for (int i = 0; i < n; i++) {
        int p;
        cin >> p;
        vector<point> pts(p);
        for (auto &pt: pts) cin >> pt.x >> pt.y;
        pts.push_back(pts.front());
        ans += area(pts);
    }
    cout << ans / 2 << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
