#include <bits/stdc++.h>
using namespace std;

typedef set<int> si;
si bad_vertices;

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int ai, bi;
        cin >> ai >> bi;
        bad_vertices.insert(ai);
        bad_vertices.insert(bi);
    }
    int good_vertex = -1;
    for (int i = 1; i <= n && good_vertex == -1; i++) {
        if (bad_vertices.find(i) == bad_vertices.end()) {
            good_vertex = i;
        }
    }
    cout << n - 1 << '\n';
    for (int i = 1; i <= n; i++) {
        if (i != good_vertex) {
            cout << good_vertex << " " << i << '\n';
        }
    }
    return 0;
}
