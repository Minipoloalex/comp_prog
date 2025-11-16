#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, x;
    cin >> n >> x;
    vector<int> a(n);
    for (auto &ai: a) cin >> ai;
    sort(a.begin(), a.end());
    int l = 0, r = n - 1;
    int64_t cur_ans = 0;
    int64_t cur_cost = 0;
    vector<int> ans; ans.reserve(n);
    while (l <= r) {
        int64_t loy1 = cur_cost / x;
        int64_t loy2 = (cur_cost + a[r]) / x;
        if (loy1 != loy2) {
            cur_ans += a[r];
            cur_cost += a[r];
            ans.push_back(a[r--]);
        }
        else {
            cur_cost += a[l];
            ans.push_back(a[l++]);
        }
    }
    cout << cur_ans << '\n';
    for (int cost: ans) cout << cost << " ";
    cout << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
