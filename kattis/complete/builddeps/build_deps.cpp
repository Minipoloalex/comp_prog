#include <bits/stdc++.h>
using namespace std;

#define VISITED 1
#define UNVISITED 0

typedef vector<int> vi;
vector<vi> AL;
vector<string> files;
vi vis;
vi ans;

void dfs_top_sort(int u) {
    vis[u] = VISITED;
    for (int v: AL[u]) {
        if (vis[v] == UNVISITED) {
            dfs_top_sort(v);
        }
    }
    ans.push_back(u);
}

int main() {
    int n;
    cin >> n;
    cin.ignore();
    AL.assign(n, vi());

    string line;
    unordered_map<string, int> um;
    int idx = 0;
    for (int i = 0; i < n; i++) {
        getline(cin, line);
        istringstream iss(line);
        string file;
        iss >> file;
        file.pop_back();
        
        auto [itr, inserted] = um.emplace(file, idx);
        if (inserted) {
            files.push_back(file);
            idx++;
        }
        
        string dependency;
        while (iss >> dependency) {
            auto [itr_dep, inserted_dep] = um.emplace(dependency, idx);
            if (inserted_dep) idx++, files.push_back(dependency);
            
            int u = um[file];
            int v = um[dependency];
            AL[v].push_back(u);
        }
    }
    // for (int u = 0; u < n; u++) {
    //     cout << u << ": ";
    //     for (int v: AL[u]) {
    //         cout << v << " ";
    //     }
    //     cout << endl;
    // }
    // for (string file: files) {
    //     cout << file << endl;
    // }

    string changed_file;
    cin >> changed_file;

    vis.assign(n, UNVISITED);
    dfs_top_sort(um[changed_file]);
    
    reverse(ans.begin(), ans.end());
    for (int file: ans) {
        cout << files[file] << endl;
    }
    return 0;
}
