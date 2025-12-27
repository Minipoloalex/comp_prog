#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> d(n);
    for (auto &di: d) cin >> di;
    vector<vector<int>> groups;
    k++;
    vector<int> cnt;
    vector<int> curg; curg.reserve(k);
    int curcnt = 0;
    for (int i = n - 1; i >= 0; ) {
        curg.clear();
        int st = i;
        int iters = (i == n - 1) ? k - 1 : k;
        for (; i >= 0 && st-i < iters; i--) {
            curg.push_back(d[i]);
        }
        groups.push_back(curg);
        cnt.push_back(curcnt++);
    }
    reverse(groups.begin(), groups.end());
    reverse(cnt.begin(), cnt.end());
    int x = cnt.front();

    // instead of using a multiset, we could use a priority queue
    // and insert all items inside and remove them one by one (the maximum at each step)
    multiset<int> ms;
    int64_t ans = 0;
    for (int i = 0; i < int(groups.size())-1; i++) {
        vector<int> &g = groups[i];
        int allowed = cnt[i];
        sort(g.rbegin(), g.rend());
        for (int j = 0; j < min(allowed, int(g.size())); j++) {
            int val = g[j];
            if (int(ms.size()) == x) {
                int mn = *ms.begin();
                if (val > mn) {
                    ms.erase(ms.find(mn));
                    ms.insert(val);
                }
            }
            else {
                ms.insert(val);
            }
        }
        int take = *prev(ms.end());
        ms.erase(prev(ms.end()));
        ans += take;
    }
    cout << ans << '\n';
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
