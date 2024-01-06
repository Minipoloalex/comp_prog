#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;


// modified UnionFind for kattis - almostunionfind
class UnionFind {                                // OOP style
private:
  vi p, rank, setSize;                           // vi p is the key part
  vi setSum;
  vector<vi> children;
  int numSets;
public:
  UnionFind(int N) {
    p.assign(N, 0); for (int i = 0; i < N; ++i) p[i] = i;
    rank.assign(N, 0);                           // optional speedup
    setSize.assign(N, 1);                        // optional feature
    setSum.resize(N);
    
    children.assign(N, vi());
    for (int i = 1; i <= N; i++) setSum[i - 1] = i;
    
    numSets = N;                                 // optional feature
  }

  int findSet(int i) { return (p[i] == i) ? i : (p[i] = findSet(p[i])); }
  bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }

  int numDisjointSets() { return numSets; }      // optional
  int sizeOfSet(int i) { return setSize[findSet(i)]; } // optional
  int sumOfSet(int i) { return setSum[findSet(i)]; }

  void unionSet(int i, int j) {
    if (isSameSet(i, j)) return;                 // i and j are in same set
    int x = findSet(i), y = findSet(j);          // find both rep items
    if (rank[x] > rank[y]) swap(x, y);           // keep x 'shorter' than y
    p[x] = y;                                    // set x under y

    children[y].push_back(x);

    if (rank[x] == rank[y]) ++rank[y];           // optional speedup
    setSize[y] += setSize[x];                    // combine set sizes at y
    setSum[y] += setSum[x];
    --numSets;                                   // a union reduces numSets
  }
  void moveToSet(int i, int j) {
    // for (int idx = 0; idx < (int) p.size(); idx++) {
    //     cout << "p[" << idx << "] = " << p[idx];
    //     cout << " setSize[" << idx << "] = " << setSize[idx];
    //     cout << " setSum[" << idx << "] = " << setSum[idx];
    //     cout << " children[" << idx << "].size() = " << children[idx].size() << endl;
    // }
    if (isSameSet(i, j)) return;
    if (sizeOfSet(i) == 1) {
        return unionSet(i, j);
    }
    int x = findSet(i);
    // cout << "Root: " << x << ", i: " << i << endl;
    int initial_num_sets = numSets;

    if (i == x) {   // root of its set -> need to select other root
        setSum[i] = i + 1;
        setSize[i] = 1;
        for (int child: children[i]) p[child] = child; // , cout << child << " ";
        // cout << endl;
        for (int c = 1; c < (int) children[i].size(); c++) {
            unionSet(children[i][c], children[i][c - 1]);
        }
    }
    else {
        int current = p[i];
        do {
            setSum[current] -= setSum[i];
            setSize[current] -= setSize[i];
            current = p[current];
        } while (current != x);
        setSum[i] = i + 1;
        setSize[i] = 1;

        // cout << "children[" << p[i] << "].size() = " << children[p[i]].size() << endl;
        auto itr = find(children[p[i]].begin(), children[p[i]].end(), i);
        if (itr != children[p[i]].end()) children[p[i]].erase(itr);
        // cout << "children[" << p[i] << "].size() = " << children[p[i]].size() << endl;

        for (int child: children[i]) p[child] = child;
        for (int c = 1; c < (int) children[i].size(); c++) {
            unionSet(children[i][c], children[i][c - 1]);
        }
        if (!children[i].empty()) {
            unionSet(children[i][0], x);
        }
    }
    p[i] = i;
    rank[i] = 0;
    children[i].clear();
    unionSet(i, j);
    numSets = initial_num_sets;
  }
};

int main() {
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    int n, m;
    while (cin >> n >> m) {
        cin.ignore();
        
        UnionFind uf(n);
        int command = 0;
        for (int i = 0; i < m; i++) {
            cin >> command;
            int p, q;
            switch (command) {
                case 1:  // union sets p and q
                    cin >> p >> q;
                    uf.unionSet(p - 1, q - 1);
                    break;
                case 2:
                    cin >> p >> q;
                    uf.moveToSet(p - 1, q - 1);
                    break;
                case 3:
                    cin >> p;
                    cout << uf.sizeOfSet(p - 1) << " " << uf.sumOfSet(p - 1) << endl;
                    break;
            }
        }
    }

    return 0;
}
