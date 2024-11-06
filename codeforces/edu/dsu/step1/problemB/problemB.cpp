#include <bits/stdc++.h>
using namespace std;

vector<int> parent;
vector<int> mn, mx, sz;

int get(int a) {
    if (a == parent[a]) return a;
    parent[a] = get(parent[a]);
    
    return parent[a];
}

void make_set(int v) {
    parent[v] = v;
    mn[v] = v;
    mx[v] = v;
    sz[v] = 1;  
}

void union_sets(int a, int b) {
    a = get(a);
    b = get(b);

    parent[b] = a;  // a will be the root
    mn[a] = min(mn[a], mn[b]);
    mx[a] = max(mx[a], mx[b]);
    if (a != b) {
        sz[a] += sz[b];
    }
}

bool same_set(int a, int b) {
    return get(a) == get(b);
}

int main() {
    int n, m;
    cin >> n >> m;

    parent.resize(n + 1);
    mn.resize(n + 1);
    mx.resize(n + 1);
    sz.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        make_set(i);
    }

    while (m--) {
        string s;
        int u, v;
        cin >> s;
        if (s == "union") {
            cin >> u >> v;
            union_sets(u, v);
        }
        else {
            cin >> u;
            assert(s == "get");
            u = get(u);
            cout << mn[u] << " " << mx[u] << " " << sz[u] << '\n';
        }
    }
    return 0;
}
