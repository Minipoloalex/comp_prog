#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &ai: a) cin >> ai;
    vector<pair<int,int>> ans(n);
    // basically, for each (i, val) in the array:
    // find the largest subarray containing i that has strength = val (i.e., all vals >= val)
    stack<int> s;
    for (int i = 0; i < n; i++) {
        int prev_index = -1;
        while (!s.empty() && a[i] <= a[s.top()]) {
            s.pop();
        }
        if (!s.empty()) {
            prev_index = s.top();
        }
        s.push(i);
        ans[i].first = prev_index;
    }

    s = stack<int>();
    for (int i = n - 1; i >= 0; i--) {
        int nxt_index = n;
        while (!s.empty() && a[i] <= a[s.top()]) {
            s.pop();
        }
        if (!s.empty()) {
            nxt_index = s.top();
        }
        s.push(i);
        ans[i].second = nxt_index;
    }
    // for (int i = 0; i < n; i++) {
    //     cout << ans[i].first << " " << ans[i].second << '\n';
    // }
    // cout << endl;
    vector<int> mxs(n + 1, 0);
    for (int i = 0; i < n; i++) {
        int sz = ans[i].second - ans[i].first - 1;
        mxs[sz] = max(mxs[sz], a[i]);
    }
    vector<int> res;
    int cur_mx = 0;
    for (int sz = n; sz >= 1; sz--) {
        cur_mx = max(cur_mx, mxs[sz]);
        res.push_back(cur_mx);
    }
    reverse(res.begin(), res.end());
    for (int r: res) cout << r << " ";
    cout << '\n';
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
