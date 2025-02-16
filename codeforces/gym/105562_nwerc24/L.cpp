#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m, x, y;
    cin >> m >> n >> x >> y;
    vector<int> a(n);
    vector<int> b(m);
    for (auto &bi: b) cin >> bi;
    for (auto &ai: a) cin >> ai;
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    auto possible = [&](int val) {
        vector<int> free(m);
        for (int i = 0; i < m; i++) {
            if (i < val) {
                free[i] = y;
            }
            else free[i] = x;
        }

        int i = 0, j = 0;
        while (i < n && j < m) {
            while (j < m && (a[i] > b[j] || free[j] == 0)) {
                j++;
            }
            if (j == m) break;

            free[j]--;
            i++;
        }
        return i == n;
    };

    int lo = 0, hi = m;
    while (lo < hi) {
        int med = lo + (hi - lo + 1) / 2;
        if (possible(med)) {
            lo = med;
        }
        else {
            hi = med - 1;
        }
    }
    if (possible(lo)) {
        cout << lo << '\n';
    }
    else {
        cout << "impossible\n";
    }
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    solve();
    return 0;
}
