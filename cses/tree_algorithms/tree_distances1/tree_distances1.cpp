#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> g;

struct mx2 {
    int mx = 0, mx_id = -1, mx2 = 0;
    void add(int value, int id) {
        if (value >= mx) {
            mx2 = mx;
            mx = value;
            mx_id = id;
        }
        else if (value >= mx2) {
            mx2 = value;
        }
    }
    int get(int id) {   // child id (cannot use its own path)
        if (id == mx_id) return mx2;
        return mx;
    }
};

vector<mx2> max_dist;

void botupdfs(int u, int p) {
    for (int v: g[u]) {
        if (v != p) {
            botupdfs(v, u);
            max_dist[u].add(max_dist[v].mx + 1, v); // v itself cannot use this path
        }
    }
}

void topdowndfs(int u, int p) {
    if (p != -1) {
        int pdist = max_dist[p].get(u);   
        max_dist[u].add(pdist + 1, -1);  // any child of u can use this path
    }
    for (int v: g[u]) {
        if (v != p) {
            topdowndfs(v, u);
        }
    }
}


void solve() {
    int n;
    cin >> n;
    max_dist.resize(n);
    g.assign(n, vector<int>());
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--;b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    botupdfs(0, -1);
    topdowndfs(0, -1);
    for (int i = 0; i < n; i++) {
        cout << max_dist[i].mx << " ";
    }
    cout << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    solve();
    return 0;
}
