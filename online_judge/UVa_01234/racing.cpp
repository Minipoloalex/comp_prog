#include <bits/stdc++.h>
using namespace std;

#define INF 1e9

typedef vector<int> vi;
typedef tuple<int, int, int> iii;
typedef vector<iii> EL;

EL edgeList;

int res;

class UnionFind {                                // OOP style
private:
  vi p, rank, setSize;                           // vi p is the key part
  int numSets;
public:
  UnionFind(int N) {
    p.assign(N, 0); for (int i = 0; i < N; ++i) p[i] = i;
    rank.assign(N, 0);                           // optional speedup
    setSize.assign(N, 1);                        // optional feature
    numSets = N;                                 // optional feature
  }

  int findSet(int i) { return (p[i] == i) ? i : (p[i] = findSet(p[i])); }
  bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }

  int numDisjointSets() { return numSets; }      // optional
  int sizeOfSet(int i) { return setSize[findSet(i)]; } // optional

  void unionSet(int i, int j) {
    if (isSameSet(i, j)) return;                 // i and j are in same set
    int x = findSet(i), y = findSet(j);          // find both rep items
    if (rank[x] > rank[y]) swap(x, y);           // keep x 'shorter' than y
    p[x] = y;                                    // set x under y
    if (rank[x] == rank[y]) ++rank[y];           // optional speedup
    setSize[y] += setSize[x];                    // combine set sizes at y
    --numSets;                                   // a union reduces numSets
  }
};

int main() {
    int c; cin >> c;
    while (c--) {
        int n, m;   // n < 10e4, m < 10e5
        cin >> n >> m;
        
        // do not forget to reset global variables (and outer loop variables, if they exist)
        res = 0;
        edgeList.clear();
        
        UnionFind uf(n);
        for (int i = 0; i < m; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            u--; v--;
            edgeList.emplace_back(w, u, v);
        }
        sort(edgeList.begin(), edgeList.end(), greater<iii>());
        for (auto &t: edgeList) {
            int w = get<0>(t);
            int u = get<1>(t);
            int v = get<2>(t);
            if (uf.isSameSet(u, v)) {
                res += w;
            }
            else {
                uf.unionSet(u, v);
            }
        }
        cout << res << endl;
    }
    return 0;
}

// start junction followed by a path with size 3+ roads leading back to the start junction eventually - this is ensured trivially
// each road in a circuit can only be traversed once in one direction
// cameras can be deployed in the roads, not the junctions
