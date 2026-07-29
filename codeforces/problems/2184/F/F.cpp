#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<vector<int>> g(n);
    for (int i = 0; i < n-1; i++) {
        int u, v;
        cin >> u >> v;
        u--;v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    bool ans = false;
    function<int(int,int)> dfs = [&](int u, int p) {
        int c2 = 0; // count of children with 2 possible values

        // values that can be generated from children
        int v1 = 0;
        int v2 = 0;
        bool v1valid = false;
        bool v2valid = false;
        for (int v: g[u]) {
            if (v != p) {
                v1valid = true;
                int cret = dfs(v, u);
                int cbits = 0;
                for (int i = 0; i < 3; i++) {
                    if (cret & (1 << i)) {
                        cbits++;
                    }
                }
                if (cbits == 3) return 0b111;
                int seen = false;
                for (int i = 0; i < 3; i++) {
                    if (cret & (1 << i)) {
                        if (cbits == 1) {
                            v1 += i;
                            v2 += i;
                        }
                        else if (cbits == 2) {
                            if (!seen) {
                                seen = true;
                                v1 += i;
                            }
                            else {
                                v2 += i;
                            }
                        }
                    }
                }
                if (cbits == 2) {
                    v2valid = true;
                    c2++;
                }
            }
        }
        if (c2 > 1) return 0b111;

        v1 %= 3;
        v2 %= 3;
        int ret = (1 << 1);
        if (v1valid) {
            ret = ret | (1 << v1);
        }
        if (v2valid) {
            ret = ret | (1 << v2);
        }
        return ret;
    };
    int ret = dfs(0, -1);
    if (ret & (1 << 0)) {
        ans = true;
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
