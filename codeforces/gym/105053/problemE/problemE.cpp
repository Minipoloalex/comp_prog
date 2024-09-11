#include <bits/stdc++.h>
using namespace std;

const int MAX_N = int(1e3) + 10;
vector<int> vis;
vector<int> el[MAX_N];

bool isbipartite(int u, int c) {
    vis[u] = c;
    for (int v: el[u]) {
        if (!vis[v]) {
            if (!isbipartite(v, 3 - c)) {
                return false;
            }
        }
        else if (vis[v] == vis[u]) return false;
    }
    return true;
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int n;
    cin >> n;
    vector<int> start(n), end(n);
    for (int i = 0; i < 2 * n; i++) {
        string s;
        cin >> s;
        int xi = stoi(s.substr(1));
        xi--;
        if (s[0] == '+') {
            start[xi] = i;
        }
        else {
            assert(s[0] == '-');
            end[xi] = i;
        }
    }
    // for (int i = 0; i < n; i++) {
    //     cout << i << " " << start[i] << " " << end[i] << endl;
    // }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (start[i] < start[j] && start[j] < end[i] && end[i] < end[j]) {
                el[i].push_back(j);
                el[j].push_back(i);
            }
        }
    }
    vis.assign(n, 0);
    bool result = true;
    for (int i = 0; i < n && result; i++) {
        if (!vis[i]) {
            result &= isbipartite(i, 1);
        }
    }
    if (!result) cout << "*\n";
    else {
        for (int i = 0; i < n; i++) {
            if (vis[i] == 1) {
                cout << "G";
            }
            else assert(vis[i] == 2), cout << "S";
        }
        cout << '\n';
    }
    return 0;
}
