#include <bits/stdc++.h>
using namespace std;

const int MAX_N = int(5e4);

typedef pair<int,int> ii;
vector<ii> pts;
int n;
vector<array<int,4>> pref;
vector<array<int,4>> suf;

ostream &operator<<(ostream &out, array<int,4> &a) {
    for (int i = 0; i < 4; i++) {
        out << a[i] << " ";
    }
    out << '\n';
    return out;
}

void setup_pref() {
    for (int i = 0; i < n; i++) {
        auto &[xmin, xmax, ymin, ymax] = pref[i];
        xmin = xmax = pts[i].first;
        ymin = ymax = pts[i].second;
        if (i - 1 >= 0) {
            auto &[pxmin, pxmax, pymin, pymax] = pref[i - 1];
            xmin = min(xmin, pxmin);
            xmax = max(xmax, pxmax);
            ymin = min(ymin, pymin);
            ymax = max(ymax, pymax);
        }
    }
    for (int i = n - 1; i >= 0; i--) {
        auto &[xmin, xmax, ymin, ymax] = suf[i];
        xmin = xmax = pts[i].first;
        ymin = ymax = pts[i].second;
        if (i + 1 < n) {
            auto &[pxmin, pxmax, pymin, pymax] = suf[i + 1];
            xmin = min(xmin, pxmin);
            xmax = max(xmax, pxmax);
            ymin = min(ymin, pymin);
            ymax = max(ymax, pymax);
        }
    }
}

int64_t area(array<int,4> &v) {
    auto &[xmin, xmax, ymin, ymax] = v;
    return (xmax - xmin) * 1LL * (ymax - ymin);
}

int64_t get_ans() {
    int64_t ans = LLONG_MAX;
    for (int i = 0; i < n - 1; i++) {
        if (pts[i].first < pts[i + 1].first) {  // same as !=
            ans = min(ans, area(pref[i]) + area(suf[i + 1]));
        }
    }
    return ans;
}

void solve() {
    freopen("split.in", "r", stdin);
    freopen("split.out", "w", stdout);
    cin >> n;

    pts.resize(n);
    suf.resize(n);
    pref.resize(n);
    for (auto &x: pts) cin >> x.first >> x.second;

    sort(pts.begin(), pts.end());
    setup_pref();
    int64_t ans_hor = get_ans();

    for (auto &[x, y]: pts) {
        swap(x, y);
    }
    sort(pts.begin(), pts.end());
    setup_pref();
    int64_t ans_ver = get_ans();

    int64_t ans = min(ans_hor, ans_ver);
    int64_t total = area(pref[n - 1]);
    cout << total - ans << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    solve();
    return 0;
}
