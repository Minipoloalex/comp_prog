#include <bits/stdc++.h>
using namespace std;

const int MAX_AI = int(1e5);

vector<pair<int,int>> factors_sqrt(int n) {
    vector<pair<int,int>> prime_factors;
    for (int i = 2; i * i <= n; i++) {
        int cnt = 0;
        while (n % i == 0) {
            n /= i;
            cnt++;
        }
        if (cnt > 0) prime_factors.emplace_back(i, cnt);
    }
    if (n > 1) prime_factors.emplace_back(n, 1);
    return prime_factors;
}

void solve() {
    int n, k;
    cin >> n >> k;

    int64_t ans = 0;
    map<vector<pair<int,int>>, int> mp;
    for (int j = 0; j < n; j++) {
        int ai;
        cin >> ai;
        vector<pair<int,int>> factors = factors_sqrt(ai);
        vector<pair<int,int>> mod_factors;
        mod_factors.reserve(factors.size());
        for (auto &[i, cnt]: factors) {
            if (cnt % k == 0) continue;
            mod_factors.emplace_back(i, k - cnt % k);
        }
        ans += mp[mod_factors];
        for (int i = 0; i < int(mod_factors.size()); i++) {
            mod_factors[i].second = -(mod_factors[i].second - k);
        }
        mp[mod_factors]++;
    }

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
