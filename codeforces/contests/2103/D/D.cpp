#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n), p(n, 0);
    for (auto &ai: a) cin >> ai;
    int mx = *max_element(a.begin(), a.end());

    int l = 1, r = n;
    int use_small = 0;
    vector<int> cur(n);
    iota(cur.begin(), cur.end(), 0);
    for (int i = 1; i <= mx; i++) {
        vector<int> ind, nxt;
        // ind has indices corresponding to the cur array
        // nxt has indices corresponding to remaining elements on the array a (original)
        // the main part of the problem lies on this logic: myin2.txt has a good example
        for (int j = 0; j < int(cur.size()); j++) {
            int idx_on_a = cur[j];
            if (a[idx_on_a] == i) {
                ind.push_back(j);
            }
            else {
                nxt.push_back(idx_on_a);
            }
        }

        int sz = int(ind.size());
        int prev = int(cur.size());
        for (int j = sz - 1; j >= 0; j--) {
            int idx = ind[j];
            int idx_on_a = cur[idx];
            if (idx != prev - 1) {
                break;
            }
            prev = idx;
            if (use_small) {
                p[idx_on_a] = l++;
            }
            else {
                p[idx_on_a] = r--;
            }
            ind.pop_back();
        }
        for (int idx: ind) {
            int idx_on_a = cur[idx];
            if (use_small) {
                p[idx_on_a] = l++;
            }
            else {
                p[idx_on_a] = r--;
            }
        }
        cur = nxt;
        use_small = 1 - use_small;
    }
    for (int i = 0; i < n; i++) {
        int v = p[i] == 0 ? l : p[i];
        cout << v << " \n"[i == n - 1];
    }
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
