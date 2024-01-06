#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
#define UNVISITED -1

vi dfs_num;
vi dfs_low;
vi dfs_parent;
vector<vi> AL;
int dfs_counter;

bool dfs_bridges(int u) {
    // cout << "Exploring vertex u: " << u << endl;
    dfs_low[u] = dfs_num[u] = dfs_counter++;
    for (int v: AL[u]) {
        if (dfs_num[v] == UNVISITED) {
            dfs_parent[v] = u;
            if (dfs_bridges(v)) return true;
            if (dfs_low[v] > dfs_num[u]) return true;
            dfs_low[u] = min(dfs_low[u], dfs_low[v]);
        }
        else if (dfs_parent[u] != v) {  // must not be trivial cycle, see first example in in1.txt
            // i.e. if current vertex being explored is not the direct child of adjacent vertex v
            dfs_low[u] = min(dfs_low[u], dfs_num[v]);
        }
    }
    return false;
}

int main() {
    int p, c;
    while (cin >> p >> c) { // p [1, 100], c [0, 5000]
        AL.clear();
        AL.assign(p, vi());
        dfs_num.assign(p, -1);
        dfs_low.assign(p, -1);
        dfs_parent.assign(p, -1);
        if (c == 0 && p == 0) break;
        for (int i = 0; i < c; i++) {
            int a, b;
            cin >> a >> b;
            AL.at(a).push_back(b);
            AL.at(b).push_back(a);
        }
        dfs_counter = 0;
        bool has_bridge = false;
        for (int u = 0; u < p; u++) {
            if (dfs_num[u] == UNVISITED) {
                if (dfs_bridges(u)) {
                    has_bridge = true;
                    cout << "Yes" << endl;
                    break;
                }
            }
        }
        if (!has_bridge) cout << "No" << endl;
        // for (int u = 0; u < p; u++) {
        //     cout << "dfs_num[" << dfs_num[u] << "] = " << dfs_num[u] << ", dfs_low[" << u << "] = " << dfs_low[u] << endl;
        // }
    }
    return 0;
}
