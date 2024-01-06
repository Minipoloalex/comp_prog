#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef tuple<double, int, int> dii;
typedef pair<double, double> dd;

vector<dii> EL;
vector<dd> islands;

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

double distance(const dd &a, const dd &b) {
    double dx = a.first - b.first;
    double dy = a.second - b.second;
    return sqrt(dx * dx + dy * dy);
}

int main() {
    int n; cin >> n;
    while (n--) {
        EL.clear();
        islands.clear();

        int m; cin >> m;
        for (int i = 0; i < m; i++) {
            double a, b; cin >> a >> b;
            islands.emplace_back(a, b);
        }
        for (int i = 0; i < m; i++) {
            for (int j = i + 1; j < m; j++) {
                double w = distance(islands[i], islands[j]);
                EL.emplace_back(w, i, j);
            }
        }
        sort(EL.begin(), EL.end());
        UnionFind uf(m);
        double res = 0;
        for (auto &[w, i, j]: EL) {
            if (!uf.isSameSet(i, j)) {
                uf.unionSet(i, j);
                res += w;
            }
        }
        cout << res << endl;
    }

    return 0;
}
