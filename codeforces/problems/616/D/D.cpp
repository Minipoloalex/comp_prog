#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (auto &ai: a) cin >> ai;

    multiset<int> s;
    int l = 0, r = 0;
    int mx = 0, cnt = 0;
    pair<int,int> ans;
    while (r < n) {
        // Could have just used an array with counts instead (to track the total count)
        auto before = s.find(a[r]);
        if (before == s.end()) {
            cnt++;
        }
        s.insert(a[r]);
        while (cnt > k) {
            auto it = s.find(a[l]);
            s.erase(it);
            if (s.find(a[l]) == s.end()) {
                cnt--;
            }
            l++;
        }

        int sz = r - l + 1;
        if (sz > mx) {
            mx = sz;
            ans = {l, r};
        }
        r++;
    }
    cout << ans.first + 1 << " " << ans.second + 1 << '\n';
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
