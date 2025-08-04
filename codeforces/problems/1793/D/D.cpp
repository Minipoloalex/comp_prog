#include <bits/stdc++.h>
using namespace std;

int n;

vector<int> find_pos(const vector<int> &perm) {
    vector<int> ans(n + 1);
    for (int i = 0; i < n; i++) {
        ans[perm[i]] = i;
    }
    return ans;
}

int64_t subarrays(int l, int r) {
    if (l <= r) {
        int len = r - l + 1;
        return int64_t(1 + len) * len / 2;
    }
    return 0;
}

void solve() {
    cin >> n;
    vector<int> p(n), q(n);
    for (auto &pi: p) cin >> pi;
    for (auto &qi: q) cin >> qi;
    int64_t ans = 0;
    vector<int> posp = find_pos(p);
    vector<int> posq = find_pos(q);

    int mn = min(posp[1], posq[1]);
    int mx = max(posp[1], posq[1]);
    ans += subarrays(0, mn - 1);
    ans += subarrays(mx + 1, n - 1);
    ans += subarrays(mn + 1, mx - 1);
    for (int i = 2; i <= n; i++) {
        int prevmn = mn, prevmx = mx;
        mn = min(mn, posp[i]);
        mn = min(mn, posq[i]);
        mx = max(mx, posp[i]);
        mx = max(mx, posq[i]);
        if ((posp[i] < prevmn || posp[i] > prevmx) && (posq[i] < prevmn || posq[i] > prevmx)) {
            // can count this MEX (counting MEX = i: contains numbers up until i - 1)
            int max_size_left = 0;
            if (posp[i] < prevmn) max_size_left = max(max_size_left, posp[i] + 1);
            if (posq[i] < prevmn) max_size_left = max(max_size_left, posq[i] + 1);
            int max_size_right = n - 1;
            if (posp[i] > prevmx) max_size_right = min(max_size_right, posp[i] - 1);
            if (posq[i] > prevmx) max_size_right = min(max_size_right, posq[i] - 1);

            ans += int64_t(prevmn - max_size_left + 1) * (max_size_right - prevmx + 1);
        }
    }
    ans++;  // complete array: mex = n + 1
    cout << ans << '\n';
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
