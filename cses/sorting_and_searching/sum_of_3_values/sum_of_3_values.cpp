#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, x;
    cin >> n >> x;
    vector<int> a(n);
    for (auto &ai: a) cin >> ai;
    vector<int> ids(n);
    iota(ids.begin(),ids.end(),0);
    sort(ids.begin(),ids.end(),[&](int i, int j) { return a[i] < a[j]; });
    array<int,3> sol = {-1,-1,-1};
    for (int i = 0; i < n; i++) {
        int l = i + 1, r = n - 1;
        while (l < r) {
            int64_t cand = a[ids[i]] + a[ids[l]] + a[ids[r]];
            if (cand == x) {
                sol = {ids[i], ids[l], ids[r]};
                break;
            }
            else if (cand < x) {
                l++;
            }
            else {
                assert(cand > x);
                r--;
            }
        }
    }
    if (sol[0] == -1) {
        cout << "IMPOSSIBLE\n";
    }
    else {
        for (int i = 0; i < 3; i++) sol[i]++;
        cout << sol[0] << " " << sol[1] << " " << sol[2] << '\n';
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
