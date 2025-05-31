#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, x;
    cin >> n >> x;
    vector<pair<int,int>> a(n);
    for (int i = 0; i < n; i++) {
        int ai;
        cin >> ai;
        a[i] = {ai, i};
    }
    sort(a.begin(), a.end());
    int l = 0, r = n - 1;
    pair<int,int> ans = {-1,-1};
    while (l < r) {
        auto &[lai, li] = a[l];
        auto &[rai, ri] = a[r];
        int sm = lai + rai;
        if (sm == x) {
            ans = {li, ri};
            break;
        }
        if (sm > x) {
            r--;
        }
        else {
            assert(sm < x);
            l++;
        }
    }
    if (ans.first == -1) {
        cout << "IMPOSSIBLE\n";
    }
    else {
        cout << ans.first + 1 << " " << ans.second + 1 << '\n';
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
