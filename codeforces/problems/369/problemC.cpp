#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
const int MAX_N = int(1e5) + 10;

bitset<MAX_N> chosen;
vii el[MAX_N];
vi vis;

void dfs(int u, int prev) {
    vis[u] = 1;
    for (auto &[v, t]: el[u]) {
        if (!vis[v]) {
            if (t == 1) {
                dfs(v, prev);
            }
            else {
                assert(t == 2);
                if (prev != -1) chosen.reset(prev);
                chosen.set(v);
                dfs(v, v);
            }
        }
    }
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int n;
    cin >> n;
    vis.assign(n, 0);
    for (int i = 0; i < n - 1; i++) {
        int xi, yi, ti; cin >> xi >> yi >> ti;
        xi--;yi--;
        el[xi].emplace_back(yi, ti);
        el[yi].emplace_back(xi, ti);
    }

    chosen.reset();
    dfs(0, -1);

    vi ans;
    for (int i = 0; i < n; i++) {
        if (chosen[i]) {
            ans.push_back(i + 1);
        }
    }

    cout << ans.size() << '\n';
    for (int v: ans) {
        cout << v << " ";
    }
    cout << '\n';
    return 0;
}
