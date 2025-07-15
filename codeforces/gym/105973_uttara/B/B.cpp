#include <bits/stdc++.h>
#define MAX 5000000
using namespace std;
int sieve[MAX+10];
const int64_t MOD = 998244353;

vector<int> mp[MAX + 10];

void build()
{
    for(int i=2;i<=MAX;++i)
    {
        if(!sieve[i])
        {
            for(int j=i;j<=MAX;j+=i)
            {
                sieve[j] = i;
            }
        }
    }
}

vector<int> factor(int x) {
    vector<int> r;
    while (x != 1) {
        r.push_back(sieve[x]);
        int tmp = sieve[x];
        while (x % tmp == 0) 
            x /= tmp;
    }
    return r;
}

void clean(vector<int>& used) {
    for (int x : used) mp[x].clear();
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &ai: a) cin >> ai;

    vector<int> used;

    for (int i = 0; i < n; i++) {
        auto pf = factor(a[i]);
        for (int p: pf) {
            used.push_back(p);
            mp[p].push_back(i);
            if (mp[p].size() >= 3) {
                cout << "0\n";
                clean(used);
                return;
            }
        }
    }

    sort(used.begin(), used.end());
    used.erase(unique(used.begin(), used.end()), used.end());

    bool has_edges = false;
    vector<vector<int>> g(n);
    
    for (int use : used) {
        auto& ids = mp[use];
        if (ids.size() <= 1) continue;
        has_edges = true;
        g[ids[0]].push_back(ids[1]);
        g[ids[1]].push_back(ids[0]);
    }
    vector<int> vis(n, 0);
    function<bool(int,int)> dfs = [&](int u, int c) {
        vis[u] = c;
        for (int v: g[u]) {
            if (!vis[v]) {
                if (!dfs(v, 3 - c)) {
                    return false;
                }
            } else if (vis[v] == c) {
                return false;
            }
        }
        return true;
    };
    int64_t ans = 1;
    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            if (!dfs(i, 2)) {
                cout << "0\n";
                clean(used);
                return;
            }
            ans = ans * 2 % MOD;
        }
    }

    if (!has_edges) ans = (ans - 2 + MOD) % MOD;
    cout << ans << '\n';
    
    clean(used);
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    build();
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
