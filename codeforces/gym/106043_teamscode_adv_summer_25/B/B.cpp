#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    auto possible = [&](int cnt) {
        int total = 0;
        while (cnt > 1) {
            total += cnt;
            cnt = (cnt + 1) / 2;
        }
        total++;
        return total <= n;
    };
    int lo = 1, hi = n;
    while (lo < hi) {
        int med = lo + (hi - lo + 1) / 2;
        if (possible(med)) {
            lo = med;
        }
        else {
            hi = med - 1;
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
