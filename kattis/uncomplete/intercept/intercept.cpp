#include <bits/stdc++.h>
using namespace std;

#define INF 1e16
#define UNVISITED -1

typedef unsigned long long ull;
typedef vector<ull> vull;

typedef queue<int> qi;

typedef vector<int> vi;
typedef pair<ull, int> ii;
typedef vector<ii> vii;

vector<vii> AL;
vector<vi> p;
vull dist;

vector<vi> AL_ssp;
vi res;


vi dfs_num;
vi dfs_low;
vi dfs_parent;
int dfs_counter;


void dfs_art_points(int u) {
    dfs_num[u] = dfs_low[u] = dfs_counter++;
    // cout << "Exploring vertex " << u << ", AL: ";
    // for (int v: AL_ssp[u]) {
    //     cout << " " << v;
    // }
    // cout << endl;
    for (int v: AL_ssp[u]) {
        if (dfs_num[v] == UNVISITED) {
            dfs_parent[v] = u;
            dfs_art_points(v);
            dfs_low[u] = min(dfs_low[u], dfs_low[v]);
            
            if (dfs_low[v] >= dfs_num[u]) {
                // cout << "Setting " << u << " to be an art point, dfs_num[" << u << "] = " << dfs_num[u] << ", dfs_low[" << v << "] = " << dfs_low[v] << endl;
                res.at(u) = 1;
            }
        }
        else if (dfs_parent[u] != v) {
            // cout << "Back edge from " << u << " to " << v << endl;
            dfs_low[u] = min(dfs_low[u], dfs_num[v]);
        }
    }
}


int main() {
    int n, m;
    cin >> n >> m;
    AL.assign(n, vii());
    p.assign(n, vi());
    for (int i = 0; i < m; i++) {
        int u, v;
        ull w;
        cin >> u >> v >> w;
        AL.at(u).emplace_back(w, v);
    }
    int s, t;
    cin >> s >> t;
    
    dist.assign(n, INF);
    dist.at(s) = 0;
    
    set<ii> pq;
    for (int i = 0; i < n; i++) pq.emplace(dist.at(i), i);

    while (!pq.empty()) {
        auto [d, u] = *pq.begin();
        pq.erase(pq.begin());
        if (u == t) break;
        for (auto &[w, v]: AL.at(u)) {
            if (dist.at(u) + w < dist.at(v)) {
                pq.erase(pq.find({dist.at(v), v}));
                
                p.at(v).clear();
                p.at(v).push_back(u);
                
                dist.at(v) = dist.at(u) + w;
                pq.emplace(dist.at(v), v);
            }
            else if (dist.at(u) + w == dist.at(v)) {
                p.at(v).push_back(u);
            }
        }
    }
    AL_ssp.assign(n, vi());
    for (int i = 0; i < n; i++) {
        for (int parent: p[i]) {
            AL_ssp[i].push_back(parent);
            AL_ssp[parent].push_back(i);
        }
    }
    // for (int i = 0; i < n; i++) {
    //     for (int val: AL_ssp[i]) {
    //         cout << val << " ";
    //     }
    //     cout << endl;
    // }
    res.assign(n, 0);
    res.at(s) = 1;
    res.at(t) = 1;

    dfs_num.assign(n, UNVISITED);
    dfs_low.assign(n, UNVISITED);
    dfs_parent.assign(n, -1);
    dfs_counter = 0;
    
    dfs_art_points(s);

    bool first = true;
    for (int i = 0; i < n; i++) {
        if (res.at(i)) {
            if (!first) cout << " ";
            cout << i;
            first = false;
        }
    }
    cout << endl;
    // for (int i = 0; i < n; i++) {
    //     cout << i << ": " << dfs_num[i] << ", " << dfs_low[i] << ", parent: " << dfs_parent[i] << endl;
    // }
    return 0;
}
