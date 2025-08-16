#include <bits/stdc++.h>
using namespace std;

typedef vector<pair<int,int>> vpii;

void solve() {
    int n, p;
    cin >> n >> p;
    vector<int> a(n);
    for (auto &ai: a) cin >> ai;
    vpii intervals;
    for (int i = 0; i < n; i++) {
        intervals.emplace_back(a[i], a[i]);
    }
    n++;
    a.insert(a.begin(), 0);
    auto possible = [&](int ops) -> bool {
        vpii myintervals = intervals;
        myintervals.emplace_back(a.back(), min(p - 1, a.back() + ops));
        int rst = (a.back() + ops) - p;
        if (rst >= 0) {
            myintervals.emplace_back(0, rst);
            for (int i = n - 2; i >= 0; i--) {
                if (a[i] == p - 1) {
                    myintervals.emplace_back(0, 0);
                }
                else {
                    myintervals.emplace_back(a[i] + 1, a[i] + 1);
                    break;
                }
            }
        }
        sort(myintervals.begin(), myintervals.end());
        int nxt = 0;
        for (auto [x, y]: myintervals) {
            if (x <= nxt) {
                nxt = max(y + 1, nxt);
            }
            else {
                break;
            }
        }
        return nxt == p;
    };
    int lo = 0, hi = p - 1;
    while (lo < hi) {
        int med = (lo + hi) / 2;
        if (possible(med)) {
            hi = med;
        }
        else {
            lo = med + 1;
        }
    }
    int ans = lo;
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
