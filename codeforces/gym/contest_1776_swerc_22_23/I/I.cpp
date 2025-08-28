#include <bits/stdc++.h>
using namespace std;

struct P {
    int64_t x, y;
	friend istream &operator>>(istream &is, P &p) {
		return is >> p.x >> p.y; }
};

int64_t area2(vector<P> pts) {
    pts.push_back(pts.front());
    int64_t ans = 0.0;
    for (int i = 0; i < (int)pts.size()-1; ++i)
        ans += (pts[i].x*pts[i+1].y - pts[i+1].x*pts[i].y);
    return abs(ans);
}

int best(const vector<P> &pts, vector<bool> &removed) {
    int n = int(pts.size());
    int64_t mn_area = INT64_MAX;
    int id = -1;
    for (int i = 0; i < n; i++) {
        if (removed[i]) continue;
        int l = (i - 1 + n) % n, r = (i + 1) % n;
        while (removed[l]) {
            l--;
            if (l < 0) l += n;
        }
        while (removed[r]) {
            r++;
            if (r >= n) r -= n;
        }
        int64_t area = area2({pts[l], pts[i], pts[r]});
        if (area < mn_area) {
            mn_area = area;
            id = i;
        }
    }
    assert(id != -1);
    return id;
}

void solve() {
    int n;
    cin >> n;
    vector<P> pts(n);
    for (auto &p: pts) cin >> p;
    vector<bool> removed(n, false);
    bool judge;
    if (n % 2 == 0) {
        judge = false;
        cout << "Alberto" << endl;
    }
    else {
        judge = true;
        cout << "Beatrice" << endl;
    }
    for (int i = 0; i < n - 2; i++, judge = !judge) {
        if (judge) {
            int q;
            cin >> q;
            q--;
            removed[q] = true;
        }
        else {
            // determine best
            int p = best(pts, removed);
            removed[p] = true;
            p++;
            cout << p << endl;
        }
    }
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
