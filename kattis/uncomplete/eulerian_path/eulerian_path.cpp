#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
#define UNVISITED -1
#define VISITED 1
int n, m;

vector<vi> AL;
int start;

vi hierholzer(int s) {
    vi ans, idx(n, 0), st;
    st.push_back(s);
    while (!st.empty()) {
        int u = st.back();
        if (idx.at(u) < int(AL.at(u).size())) {
            st.push_back(AL.at(u).at(idx.at(u)));
            idx.at(u)++;
        }
        else {
            // the top vertex of st is push into res if that vertex is already exhausted
            ans.push_back(u);
            st.pop_back();
        }
    }
    return ans;
}


bool is_eulerian_graph() {
    vi in_degree(n, 0);
    vi out_degree(n, 0);
    for (int u = 0; u < n; u++) {
        out_degree[u] += AL[u].size();
        for (int v: AL[u]) in_degree[v]++;
    }
    int count_start = 0;
    int count_end = 0;
    for (int i = 0; i < n; i++) {
        if (in_degree[i] == out_degree[i] - 1) {    // out > in
            start = i;
            count_start++;
        }
        else if (out_degree[i] == in_degree[i] - 1) {   // in > out
            count_end++;
        }
        else if (out_degree[i] != in_degree[i]) return false;

        if (count_end > 1 || count_start > 1) return false;
    }


    vector<vi> AL_undirected(n, vi());
    for (int u = 0; u < n; u++) {
        for (int v: AL[u]) {
            AL_undirected[u].push_back(v);
            AL_undirected[v].push_back(u);
        }
    }
    vi und_vis(n, UNVISITED);

    queue<int> q;
    q.push(start);
    und_vis[start] = VISITED;
    int v_count = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        v_count++;
        for (int v: AL_undirected[u]) {
            if (und_vis[v] == UNVISITED) {
                und_vis[v] = VISITED;
                q.push(v);
            }
        }
    }
    if (v_count < n) return false;
    
    return true;
}

int main() {
    while (cin >> n >> m) {
        if (n == 0 && m == 0) break;
        AL.assign(n, vi());
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            AL.at(u).push_back(v);
        }
        start = 0;
        if (!is_eulerian_graph()) { // may change start global variable
            cout << "Impossible" << endl;
        }
        else {
            vi ans = hierholzer(start);
            bool first = true;
            for (int i: ans) {
                if (!first) cout << " ";
                cout << i;
                first = false;
            }
            cout << endl;
        }
    }
    return 0;
}
