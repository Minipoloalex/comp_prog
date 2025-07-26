#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    vector<int> prefmax(n + 1, 0);
    int cur = 0;
    for (int i = 1; i <= n; i++) {
        if (a[i] > cur) cur++;
        else if (a[i] < cur) cur--;
        prefmax[i] = max(prefmax[i - 1], cur);
    }
    auto possible = [&](int x) {
        if (prefmax[n - 1] >= x) {
            return true;
        }
        for (int i = n; i >= 2; i--) {
            if (a[i] >= x) {
                x--;
            }
            else {
                x++;
            }
            if (prefmax[i - 2] >= x) {
                return true;
            };
        }
        return false;
    };
    int lo = 0, hi = n;
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
