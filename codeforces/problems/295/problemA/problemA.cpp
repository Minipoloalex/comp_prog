#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m, k;
    cin >> n >> m >> k;

    vector<int64_t> a(n);
    for (auto &x: a) cin >> x;

    vector<int64_t> pref(n, 0);

    vector<tuple<int,int,int>> ops(m);
    for (auto &[x, y, z]: ops) cin >> x >> y >> z;

    vector<int64_t> ops_pref(m, 0);
    for (int i = 0; i < k; i++) {
        int x, y;
        cin >> x >> y;
        x--; y--;
        ops_pref[x]++;
        if (y + 1 < m) {
            ops_pref[y + 1]--;
        }
    }
    for (int i = 1; i < m; i++) {
        ops_pref[i] += ops_pref[i - 1];
    }

    for (int i = 0; i < m; i++) {
        int64_t ops_count = ops_pref[i];
        auto &[li, ri, di] = ops[i];
        li--;
        ri--;
        int64_t actual_di = di * ops_count;

        pref[li] += actual_di;
        if (ri + 1 < n) pref[ri + 1] -= actual_di;
    }
    for (int i = 1; i < n; i++) {
        pref[i] += pref[i - 1];
    }
    for (int i = 0; i < n; i++) {
        cout << a[i] + pref[i] << " ";
    }
    cout << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    solve();
    return 0;
}
