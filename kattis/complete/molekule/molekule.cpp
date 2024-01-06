#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;

vector<vi> AL;
vi colors;

vii input;

void bipartite_coloring(int v, int color) {
    colors.at(v) = color;
    for (int n: AL[v]) {
        if (colors[n] != -1) continue;
        bipartite_coloring(n, 1 - color);
    }
}


int main() {
    // N molecules bound together by N - 1 bonds
    int n;
    cin >> n;
    AL.resize(n);
    
    colors.resize(n);
    colors.assign(n, -1);
    for (int i = 0; i < n - 1; i++) {
        int ai, bi; cin >> ai >> bi;    // ai and bi are connected by covalent bonds
        ai--; bi--;
        AL.at(ai).push_back(bi);
        AL.at(bi).push_back(ai);
        input.emplace_back(ai, bi);
    }

    for (int i = 0; i < n; i++) {
        if (colors.at(i) == -1) {
            bipartite_coloring(i, 0);
        }
    }
    
    // maximize stability, i.e. minimize instability
    // if the resulting directed graph is bipartite
    // then the longest path an impulse can take during its travel is minimal
    // simply color the vertices with 0 and 1 and direct the edges from 1 to 0
    for (ii &p: input) {
        int ai = p.first, bi = p.second;
        if (colors[ai] == 0 && colors[bi] == 1) {
            cout << 0 << endl;
        }
        else if (colors[ai] == 1 && colors[bi] == 0) {
            cout << 1 << endl;
        }
        else while (1);
    }
    return 0;
}
