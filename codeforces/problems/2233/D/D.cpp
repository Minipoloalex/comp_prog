#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &x: a) cin >> x;

    vector<int> aun = a;
    sort(aun.begin(), aun.end());
    aun.erase(unique(aun.begin(), aun.end()), aun.end());
    auto get_id = [&](int v) {
        return int(lower_bound(aun.begin(), aun.end(), v) - aun.begin());
    };
    for (int i = 0; i < n; i++) {
        a[i] = get_id(a[i]);
    }

    vector<vector<pair<int,int>>> g(n);

    {
        int cur = a[0];
        pair<int,int> gr = {0, 0}; // [inc, exc)
        for (int i = 1; i < n; i++) {
            if (a[i] == a[i-1]) {
                gr.second++;
            }
            else {
                g[cur].push_back(gr);
                gr = {i, i};
            }
            cur = a[i];
        }
        g[cur].push_back(gr);
    }

    vector<int> vis;
    auto check = [&](vector<int> &vec) {
        vis.assign(n, 0);
        vis[vec[0]] = 1;
        int cur = vec[0];
        for (int i = 1; i < n; i++) {
            if (cur != vec[i]) {
                if (vis[vec[i]]) return false;
            }
            cur = vec[i];
            vis[cur] = 1;
        }
        return true;
    };
    auto test_swap = [&](vector<int> &vec, int i, int j) {
        if (j < 0 || j >= n) {
            return false;
        }
        swap(vec[i], vec[j]);
        bool ret = check(vec);
        swap(vec[i], vec[j]);
        return ret;
    };
    function<bool(int)> go = [&](int i) {
        vector<int> test = a;
        bool good = false;

        int sz = int(g[i].size());
        for (int gid = 0; gid < sz; gid++) {
            auto &[l, r] = g[i][gid];
            for (int otgid = 0; otgid < sz; otgid++) {
                if (otgid == gid) continue;
                auto &[otl, otr] = g[i][otgid];

                good = good || test_swap(test, l, otl-1);
                good = good || test_swap(test, l, otr+1);
                good = good || test_swap(test, r, otl-1);
                good = good || test_swap(test, r, otr+1);
            }
        }
        return good;
    };

    bool ans = true;
    for (int i = 0; i < n; i++) {
        if (g[i].size() > 3) {
            ans = false;
            break;
        }
        else if (g[i].size() >= 2 && g[i].size() <= 3) {
            // we should try on this one to see if possible
            ans = go(i);
            break;
        }
    }
    cout << (ans ? "YES" : "NO") << '\n';
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
