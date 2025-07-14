#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    int64_t s, x;
    cin >> n >> s >> x;
    vector<int64_t> a(n);
    for (auto &ai: a) cin >> ai;

    int64_t ans = 0;
    vector<int64_t> pref(n + 1, 0);
    for (int i = 0; i < n; i++) {
        pref[i + 1] = pref[i] + a[i];
    }
    map<int64_t,int64_t> waiting, current;
    waiting[0]++;
    for (int i = 0; i < n; i++) {
        int64_t prefsum = pref[i + 1];
        int64_t look_for = prefsum - s;
        if (a[i] == x) {
            for (auto &[k, v]: waiting) {
                current[k] += v;
            }
            waiting.clear();
        }
        else if (a[i] > x) {
            waiting.clear();
            current.clear();
        }
        auto it = current.find(look_for);
        if (it != current.end()) {
            int64_t cnt = it->second;
            ans += cnt;
        }
        waiting[prefsum]++;
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
