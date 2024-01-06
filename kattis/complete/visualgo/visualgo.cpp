#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;

#define INF 1e9


vector<vii> AL;
vector<vi> p;
vi dist;
vi dp_paths;
int s, t;

int count_paths(int u) {
    if (dp_paths[u] != -1) return dp_paths[u];
    int res = 0;
    for (int parent: p.at(u)) {
        res += count_paths(parent);
    }
    // cout << "vertex " << u << " paths: " << res << endl;
    return dp_paths.at(u) = res;
}

int main() {
    // 0, V - 1
    // s and t random
    int V, E;
    cin >> V >> E;
    AL.assign(V, vii());

    for (int i = 0; i < E; i++) {        
        int u, v, w; cin >> u >> v >> w;
        AL.at(u).emplace_back(w, v);
    }
    cin >> s >> t;
    p.assign(V, vi());
    dist.assign(V, INF);
    dist.at(s) = 0;

    set<ii> pq; // (dist, vertex)
    for (int i = 0; i < V; i++) pq.emplace(dist[i], i);
    // cout << "Starting Dijkstra's" << endl;
    while(!pq.empty()) {
        auto [d, u] = *pq.begin();
        pq.erase(pq.begin());
        for (auto &[w, v]: AL[u]) {
            // cout << "u: " << u << ", v: " << v << ", w: " << w << endl;
            if (dist[u] + w < dist[v]) {  // relax edge
                pq.erase(pq.find({dist[v], v}));
                dist[v] = dist[u] + w;
                p[v].clear();
                p[v].push_back(u);
                pq.emplace(dist[v], v);
            }
            else if (dist[u] + w == dist[v]) {
                p[v].push_back(u);  // equal to best shortest path, want to count all of the shortest paths
            }
        }
    }

    // use parents assigned, the spanning tree for the DAG order
    dp_paths.assign(V, -1);
    dp_paths[s] = 1;
    // cout << "s: " << s << ", t: " << t << endl;
    // for (int parent: p[t]) {
    //     cout << parent << " ";
    // }
    // cout << endl;
    cout << count_paths(t) << endl;
    return 0;
}
