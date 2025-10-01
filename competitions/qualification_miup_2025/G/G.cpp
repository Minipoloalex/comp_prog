#include <bits/stdc++.h>
using namespace std;

#define sz(v) int((v).size())

void solve() {
    int64_t n, k;
    cin >> n >> k;
    int64_t ans = 0;
    vector<pair<int64_t,int64_t>> p;
    p.emplace_back(0,1);
    if (k < n) {
        n--;
        while (true && sz(p) < k + 1) {
            auto [cost, sz] = p.back();
            if (sz * (k-1) + 1 <= n) {
                n -= sz * (k-1) + 1;
                int64_t part_cost = cost * (k-1) + 1;
                ans += part_cost;
                p.emplace_back(cost*k+1, k*sz+1);
            }
            else {
                break;
            }
        }
        if (sz(p) == k + 1) {
            ans += n;
        }
        else {
            while (!p.empty()) {
                auto [cost, sz] = p.back();
                int64_t how_many = n / sz;
                ans += how_many * cost;
                n -= how_many * sz;
                p.pop_back();
            }
        }
    }
    cout << ans << '\n';
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    int t = 1;
    // cin >> t;
    while (t--) { 
        solve();
    }
    return 0;
}
