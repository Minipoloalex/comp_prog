#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;

vector<vi> gr;
vi indeg, vis;

void setup_indeg(int u) {
    for (int v: gr[u]) {
        if (vis[v] != 2) {   // if node first handled in this topoSort (vis[v] = 0 or 1)
            indeg[v]++;
            if (vis[v] == 0) {
                setup_indeg(v);
            }
            vis[v] = 1;
        }
    }
}

vi topoSort(int u) {
    if (vis[u]) return {};
    setup_indeg(u);
    vi ret;

    priority_queue<int> q;
    q.push(u);
    while (!q.empty()) {
        int i = q.top();
        q.pop();
        ret.push_back(i);
        vis[i] = 2;     // completely handled

        for (int v: gr[i]) {
            if (vis[v] != 2 && --indeg[v] == 0) {   // being handled during this topoSort
                q.push(v);
            }
        }
    }
    reverse(ret.begin(), ret.end());
    return ret;
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int n, m;
    cin >> n >> m;
    indeg.assign(n, 0);
    vis.assign(n, 0);
    gr.assign(n, vi());
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        gr[b - 1].push_back(a - 1);
    }
    for (int i = 0; i < n; i++) {
        // cout << "Handling " << i << ":" << endl;
        vi ans = topoSort(i);
        for (int a: ans) cout << a + 1 << " ";
        // cout << endl;
    }
    cout << '\n';

    return 0;
}
