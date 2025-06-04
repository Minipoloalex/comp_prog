#include <bits/stdc++.h>
using namespace std;

class dsu {
    vector<int> parent, rnk;
public:
    dsu(int n) {
        parent.resize(n);
        rnk.assign(n, 1);
        iota(parent.begin(), parent.end(), 0);
    }
    int get(int i) {
        return parent[i] = (parent[i] == i ? i : get(parent[i]));
    }
    void unite(int i, int j) {
        int pi = get(i);    // "going to be the new parent" (swapped if necessary)
        int pj = get(j);
        if (pi == pj) return;
        if (rnk[pi] < rnk[pj]) {
            swap(pi, pj);
        }
        // rnk[pi] >= rnk[pj]
        if (rnk[pi] == rnk[pj]) rnk[pi]++;
        parent[pj] = pi;
    }
};

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    return 0;
}
