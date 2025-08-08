#include <bits/stdc++.h>
using namespace std;

struct P {
    int x, y;
    friend istream &operator>>(istream &iss, P &p) {
        return iss >> p.x >> p.y;
    }
};

// vectors
int64_t cross(P a, P b) { return int64_t(a.x)*b.y - int64_t(a.y)*b.x; }

P toVec(P &a, P &b) {
    return P{b.x-a.x, b.y-a.y};
}

bool ccw(P &p, P &q, P &r) {
  return cross(toVec(p, q), toVec(p, r)) > 0;
}

void sort_jarvis(vector<pair<P,int>> &pts) {
    P p0 = pts[0].first;    // use pts[0] as the pivot
    sort(++pts.begin(), pts.end(), [&](pair<P,int> &a, pair<P,int> &b) {
        P ap = toVec(p0, a.first);
        P bp = toVec(p0, b.first);
        int ha = ap.y > 0 ? 1 : 0;
        int hb = bp.y > 0 ? 1 : 0;
        if (ha != hb) return ha < hb;
        return ccw(p0, a.first, b.first);
    });
    // for (auto &[p, _]: pts) {
    //     cout << p.x << " " << p.y << '\n';
    // }
    // cout << endl;
}

void solve() {
    int n;
    cin >> n;
    if (n == 2) {
        cout << "0\n";
        return;
    }
    vector<pair<P,int>> origpts(n);
    int64_t sm = 0;
    for (auto &[p, g]: origpts) {
        cin >> p >> g;
        sm += g;
    }
    vector<pair<P,int>> pts(n);
    int64_t ans = INT64_MAX;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            pts[j] = origpts[j];
        }
        swap(pts[0], pts[i]);
        sort_jarvis(pts);

        P p0 = pts[0].first;
        int cntb = 0;
        int64_t b = 0;
        int r = 2;
        int cnt = 0;
        for (int j = 1; j < n; j++) {
            P p1 = pts[j].first;
            if (cntb > 0) {
                b -= pts[j].second;
                cntb--;
            }

            while ((cntb < n - 2 && ccw(p0, p1, pts[r].first)) || r == 0) {
                if (r != 0) {
                    b += pts[r].second;
                    cntb++;
                }
                cnt++;
                r = (r + 1) % n;
                if (cnt > int(8e3)) {
                    exit(1);
                }
            }
            int64_t a = sm - pts[0].second - pts[j].second - b;
            ans = min(ans, abs(b - a));
        }
    }
    cout << ans << '\n';
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
