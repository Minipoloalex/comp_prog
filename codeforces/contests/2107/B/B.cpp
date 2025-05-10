#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (auto &ai: a) cin >> ai;
    int64_t all_zero = accumulate(a.begin(), a.end(), 0LL);
    int mn = *min_element(a.begin(), a.end());
    int mx = *max_element(a.begin(), a.end());
    int mx_cnt = (int)count(a.begin(), a.end(), mx);
    string ans;
    if (mx - mn > k + 1 || (mx - mn > k && mx_cnt > 1)) {
        ans = "Jerry";
    }
    else if (all_zero % 2 == 0) {
        ans = "Jerry";
    }
    else {
        ans = "Tom";
    }
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
