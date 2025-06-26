#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;
    int64_t k;
    cin >> k;
    vector<vector<int64_t>> g(n, vector<int64_t>(m));
    for (auto &v: g) {
        for (auto &x: v) cin >> x;
    }
    auto getidx = [&](int r, int c) {
        if (n < m) return r;
        return c;
    };
    // maybe determine the possibilities up until the x + y = 20 diagonal
    // recursive way because idk how to do iterative here
    // how to combine the paths? easy, just look for the other bits that we need
    // only TLEs with the compile flags

    // I used only one function, but maybe should have used two different versions
    // See editorial solution (simpler code): uses two different functions
    // has map for frequencies in each position, with answer computation on-the-fly for the second function
    vector<pair<vector<int64_t>, vector<int64_t>>> v(min(n,m));
    function<void(int,int,int64_t,int,int)> meet = [&](int r, int c, int64_t cur, int fin, bool fst) {
        if (r + c == fin) {
            if (fst) {
                // use the results from (r,c)
                v[getidx(r, c)].first.push_back(cur ^ g[r][c]);
            }
            else {
                v[getidx(n - r - 1, m - c - 1)].second.push_back(cur);
            }
            return;
        }

        if (r + 1 < n) {
            meet(r + 1, c, cur ^ g[r][c], fin, fst);
        }
        if (c + 1 < m) {
            meet(r, c + 1, cur ^ g[r][c], fin, fst);
        }
    };
    meet(0,0,0,max(n,m)-1,1);
    for (auto &vec: g) reverse(vec.begin(), vec.end());
    reverse(g.begin(),g.end());
    meet(0,0,0,min(n,m)-1,0);

    int64_t ans = 0;
    for (auto &[v1, v2]: v) {
        sort(v2.begin(), v2.end());
        for (int64_t val: v1) {
            int64_t look_for = k ^ val;
            ans += upper_bound(v2.begin(), v2.end(), look_for) - lower_bound(v2.begin(), v2.end(), look_for);
        }
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
