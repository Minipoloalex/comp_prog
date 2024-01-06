#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef queue<int> qi;
typedef vector<qi> vqi;

vqi flavour_positions;
struct cmp {
    bool operator()(const int &a, const int &b) const {
        // check if the returns are correct
        qi &qa = flavour_positions.at(a - 1);
        qi &qb = flavour_positions.at(b - 1);
        if (qa.empty()) return true;    // want to remove this one since empty
        if (qb.empty()) return false;
        
        return qa.front() > qb.front();   // want to remove the one that's farther away
    }
};
int main() {
    unsigned int n, m, k;
    cin >> n >> m >> k;
    vi c(n);
    flavour_positions.assign(m, qi());

    set<int, cmp> pq;    // priority_queue<int>> max size = k (ice cream machines)
    for (uint i = 0; i < n; i++) {
        cin >> c[i];
        flavour_positions.at(c[i] - 1).push(i);
    }
    int ans = 0;
    for (uint i = 0; i < n; i++) {
        int flavour = c[i];
        // cout << flavour << ", pq.begin() = " << *pq.begin();
        // cout << "[ ";
        // for (int a: pq) {
        //     cout << a << " ";
        // }
        // cout << "]" << endl;
        if (pq.find(flavour) != pq.end()) {
            // flavour already in a machine
            pq.erase(pq.find(flavour));
            
            qi &positions = flavour_positions.at(flavour - 1);
            positions.pop();
            
            pq.insert(flavour);
            continue;
        }
        ans++;
        if (pq.size() < k) {
            qi &positions = flavour_positions.at(flavour - 1);
            positions.pop();
        
            pq.insert(flavour);
        }
        else {  // pq.size() == k
            pq.erase(pq.begin());
            
            qi &positions = flavour_positions.at(flavour - 1);
            positions.pop();
            
            pq.insert(flavour);
        }
    }
    cout << ans << endl;
    return 0;
}
