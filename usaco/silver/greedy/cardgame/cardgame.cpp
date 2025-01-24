#include <bits/stdc++.h>
using namespace std;

// A much better implemented solution:
// https://usaco.guide/problems/usaco-573-high-card-low-card/solution

void solve() {
    freopen("cardgame.in", "r", stdin);
    freopen("cardgame.out", "w", stdout);
    int n;
    cin >> n;
    set<int> e, ef, es;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        e.insert(x);
        if (i < n / 2) {
            ef.insert(x);
        }
        else es.insert(x);
    }

    set<int> bf, bs;
    for (int i = 1; i <= 2 * n; i++) {
        if (e.find(i) == e.end()) {
            // the smallest cards will always be played in the second part
            // the biggest always in the first part
            if (int(bs.size()) < n / 2) bs.insert(i);
            else bf.insert(i);
        }
    }

    int ans = 0;
    while (!ef.empty()) {   // same as bf.empty()
        auto itef = --ef.end();
        int emx = *itef;
        ef.erase(itef);

        auto itbf = --bf.end();
        int bmx = *itbf;
        

        if (bmx > emx) {
            // bessie can win
            // use largest card
            bf.erase(itbf);
            ans++;
        }
        else {
            // play smallest card (worst)
            bf.erase(bf.begin());
        }
    }
    
    while (!es.empty()) {   // same as bs.empty()
        auto ites = es.begin();
        int emn = *ites;
        es.erase(ites);

        auto itbs = bs.begin();
        int bmn = *itbs;
        

        if (bmn < emn) {
            // bessie can win
            // use smallest card
            bs.erase(itbs);
            ans++;
        }
        else {
            // play largest card (worst)
            bs.erase(--bs.end());
        }
    }
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    solve();
    return 0;
}
