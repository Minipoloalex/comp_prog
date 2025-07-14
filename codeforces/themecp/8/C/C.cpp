#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    vector<int> a(n);
    for (auto &ai: a) cin >> ai;
    auto possible = [&](int mx) {
        int cnt = 0;
        bool active = false;
        for (int i = 0; i < n; i++) {
            if (s[i] == 'B') {
                if (!active && a[i] > mx) {
                    active = true;
                    cnt++;
                }
            }
            else {
                if (active && a[i] > mx) {
                    active = false;
                }
            }
        }
        return cnt <= k;
    };
    int lo = 0, hi = *max_element(a.begin(), a.end());
    while (lo < hi) {
        int m = lo + (hi - lo) / 2;
        if (possible(m)) {
            hi = m;
        }
        else {
            lo = m + 1;
        }
    }
    cout << lo << '\n';
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
