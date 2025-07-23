#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<array<int,4>> gates(n);
    for (auto &[t1, a1, t2, a2]: gates) {
        char c1, c2;
        cin >> c1 >> a1 >> c2 >> a2;
        t1 = c1 == 'x' ? 1 : 0;
        t2 = c2 == 'x' ? 1 : 0;
    }
    // at each step, we should place our additional guys
    // on the side that has the first larger multiplication (lexicographically by multiplication values)
    vector<int> suf(n + 1, -1);
    for (int i = n - 1; i >= 0; i--) {
        auto &[t1, a1, t2, a2] = gates[i];

        suf[i] = suf[i + 1];
        if (t1 == 1 && t2 == 0) {
            suf[i] = 1;
        }
        else if (t1 == 0 && t2 == 1) {
            suf[i] = 2;
        }
        else if (t1 == 1 && t2 == 1) {
            if (a1 > a2) {
                suf[i] = 1;
            }
            else if (a2 > a1) {
                suf[i] = 2;
            }
        }
    }
    auto apply = [&](int64_t cur, int type, int amount) -> int64_t {
        if (type == 1) {
            return cur * (amount - 1);
        }
        return amount;
    };
    int64_t lef = 1, rig = 1;
    for (int i = 0; i < n; i++) {
        auto &[t1, a1, t2, a2] = gates[i];
        int64_t additional = apply(lef, t1, a1) + apply(rig, t2, a2);

        int who = suf[i + 1];
        if (who == 1) {
            lef += additional;
        }
        else {
            rig += additional;
        }
    }
    cout << lef + rig << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
