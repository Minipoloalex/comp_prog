#include <bits/stdc++.h>
using namespace std;

vector<int> parent, xp;

void make_set(int v) {
    xp[v] = 0;
    parent[v] = v;
}

// 2e5 * 100 = 2e7 -> fine for int

pair<int, int> get(int a) {
    if (a == parent[a]) return { a, xp[a] };

    auto [root, rst] = get(parent[a]);

    int total = rst + xp[a];
    xp[a] = total - xp[root];   // everything that does not come from the root must be accounted in my xp
    parent[a] = root;

    return { root, total };
}

void union_sets(int a, int b) {
    a = get(a).first;
    b = get(b).first;

    if (a == b) return;
    parent[b] = a;
    xp[b] -= xp[a]; // decrement b's xp by the xp of a (since b did not actually gain it)
}

bool same_set(int a, int b) {
    return get(a).first == get(b).first;
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int n, m;
    cin >> n >> m;

    parent.resize(n + 1);
    xp.resize(n + 1);
    for (int i = 1; i <= n; ++i) make_set(i);

    while (m--) {
        string s;
        cin >> s;
        if (s == "join") {
            int x, y;
            cin >> x >> y;
            union_sets(x, y);
        }
        else if (s == "add") {
            int x, v;
            cin >> x >> v;
            auto [root, _] = get(x);
            xp[root] += v;
        }
        else {
            assert(s == "get");
            int x;
            cin >> x;
            auto [root, total] = get(x);
            cout << total << '\n';
        }
    }
    return 0;
}
