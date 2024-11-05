#include <bits/stdc++.h>
using namespace std;

vector<int> parent;

void make_set(int v) {
    parent[v] = v;
}

int get(int a) {
    if (a == parent[a]) return a;
    return parent[a] = get(parent[a]);
}

void union_sets(int a, int b) {
    a = get(a);
    b = get(b);
    parent[b] = a;
}

bool same_set(int a, int b) {
    return get(a) == get(b);
}

int main() {
    int n, m;
    cin >> n >> m;

    parent.resize(n + 1);
    for (int i = 1; i <= n; i++) make_set(i);

    while (m--) {
        string s;
        int u, v;
        cin >> s >> u >> v;
        if (s == "union") {
            union_sets(u, v);
        }
        else {
            assert(s == "get");
            cout << (same_set(u, v) ? "YES" : "NO") << '\n';
        }
    }
    return 0;
}
