#include <bits/stdc++.h>
using namespace std;

vector<int> parent, rnk, mx;

void make_set(int v) {
    parent[v] = v;
    rnk[v] = 0;
    mx[v] = v;
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

        mx[a] = max(mx[a], mx[b]);
        parent[b] = a;
        if (rnk[a] == rnk[b])
            rnk[a]++;
    }
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int n, m;
    cin >> n >> m;

    parent.resize(n + 2);
    rnk.resize(n + 2);
    mx.resize(n + 2);
    for (int i = 1; i <= n + 1; i++) {
        make_set(i);
    }

    while (m--) {
        char c;
        cin >> c;
        int x;
        cin >> x;
        if (c == '-') {
            union_sets(x, x + 1);
        }
        else {
            int root = find_set(x);
            cout << (mx[root] == n + 1 ? -1 : mx[root]) << '\n';
        }
    }
    return 0;
}
