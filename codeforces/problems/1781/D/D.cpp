#include <bits/stdc++.h>
using namespace std;

vector<int> divisors(int n) {
    vector<int> ans;
    for (int64_t i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            ans.push_back(int(i));
            if (n / i != i) {
                ans.push_back(int(n / i));
            }
        }
    }
    return ans;
}

const int64_t MAX = int64_t(1e18);

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &ai: a) cin >> ai;
    int ans = 1;
    for (int i = 0; i < n; i++) {
        vector<int> diffs;
        for (int j = i + 1; j < n; j++) {
            diffs.push_back(a[j] - a[i]);
        }
        for (int j = 0; j < int(diffs.size()); j++) {
            int diff = diffs[j];
            vector<int> divs = divisors(diff);  // sqrt(1e9)
            for (int d: divs) { // not sqrt(1e9), because |divisors| is not square root
                if ((d + diff / d) % 2 == 1 || (diff / d - d) % 2 == 1) continue;
                int p = (diff / d - d) / 2;
                // int q = (d + diff / d) / 2;
                int64_t x = int64_t(p) * p - a[i];
                if (x < 0 || x > MAX) continue;
                int cur = 0;
                for (int k = 0; k < n; k++) {
                    int64_t v = a[k] + x;
                    int64_t sqrtv = int64_t(sqrt(v));
                    if (sqrtv * sqrtv == v) {
                        cur++;
                    }
                }
                ans = max(ans, cur);
            }
        }
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
