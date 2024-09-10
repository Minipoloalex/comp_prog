#include <bits/stdc++.h>
using namespace std;

const int64_t MOD = int64_t(998244353);
const int MAX_N = int(3e5) + 10;

typedef vector<int> vi;
vi el[MAX_N];
vi vis;

bool bipartite(int u, int c, int &s1, int &s2) {
    vis[u] = c;
    if (c == 0) s1++;
    else assert(c == 1), s2++;

    for (int v: el[u]) {
        if (vis[v] == c) {
            return false;
        }
        else if (vis[v] == -1) {
            if (!bipartite(v, 1 - c, s1, s2)) {
                return false;
            }
        }
    }
    return true;
}

int64_t modpow(int64_t b, int64_t e, int64_t m) {
    // Could have precomputed this in O(N), but for this problem there is no need
    int64_t ans = 1;
    for (int i = 0; i < e; i++) {
        (ans *= b) %= m;
    }
    return ans;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        vis.assign(n, -1);
        for (int i = 0; i < n; i++) el[i].clear();

        for (int i = 0; i < m; i++) {
            int ai, bi;
            cin >> ai >> bi;
            ai--; bi--;
            el[ai].push_back(bi);
            el[bi].push_back(ai);
        }

        bool result = true;
        int64_t ans = 1;
        for (int i = 0; i < n && result; i++) {
            // cout << i << " ";
            if (vis[i] == -1) {
                int a = 0, b = 0;   // sizes of both of the bipartite graph sets
                bool isbipartite = bipartite(i, 1, a, b);
                result &= isbipartite;
                int64_t cnta = modpow(2, a, MOD);
                int64_t cntb = modpow(2, b, MOD);
                int64_t cnt = (cnta + cntb) % MOD;
                // cout << a << " " << b;
                (ans *= cnt) %= MOD;
            }
            // cout << endl;
        }
        if (!result) ans = 0;
        cout << ans << '\n';
    }
    return 0;
}
