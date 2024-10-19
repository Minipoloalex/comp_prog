#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        vector<int> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];

        map<int, int> f;
        for (int ai: a) {
            f[ai]++;
        }
        int ans = 0, curr = 0;
        deque<pair<int, int>> dq;
        for (auto &[v, freq]: f) {
            if (!dq.empty() && dq.back().first != v - 1) {
                curr = 0;
                dq.clear();
            }
            dq.emplace_back(v, freq);
            curr += freq;
            while (int(dq.size()) > k) {
                auto &[_, rmvfreq] = dq.front();
                curr -= rmvfreq;
                dq.pop_front();
            }
            ans = max(ans, curr);
        }
        cout << ans << '\n';
    }
    return 0;
}
