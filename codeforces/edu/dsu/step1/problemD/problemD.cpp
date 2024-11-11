#include <bits/stdc++.h>
using namespace std;

vector<int> parent, rnk;

void make_set(int v) {
    parent[v] = v;
    rnk[v] = 0;
}

int find_set(int v) {
    if (v == parent[v])
        return v;
    return parent[v] = find_set(parent[v]);
}

void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        if (rnk[a] < rnk[b])
            swap(a, b);
        parent[b] = a;
        if (rnk[a] == rnk[b])
            rnk[a]++;
    }
}


int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int n, m, k;
    cin >> n >> m >> k;

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
    }
    parent.resize(n + 1);
    rnk.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        make_set(i);
    }
    vector<tuple<string, int, int>> ops;
    ops.reserve(k);
    for (int i = 0; i < k; i++) {
        string s;
        int u, v;
        cin >> s >> u >> v;
        ops.emplace_back(s, u, v);
    }
    vector<string> res;
    while (k--) {
        auto &[s, u, v] = ops[k];
        if (s == "cut") {
            union_sets(u, v);
        }
        else {
            assert(s == "ask");
            string ans = find_set(u) == find_set(v) ? "YES" : "NO";
            res.push_back(ans);
        }
    }
    for (auto it = res.rbegin(); it != res.rend(); it++) {
        cout << *it << '\n';
    }
    return 0;
}
