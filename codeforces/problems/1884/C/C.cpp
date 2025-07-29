#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<pair<int,int>> events1, eventsm;
    for (int i = 0; i < n; i++) {
        int l, r;
        cin >> l >> r;
        if (l != 1) {
            events1.emplace_back(l, 0);  // for same position, open all before closing any
            events1.emplace_back(r, 1);
        }
        if (r != m) {
            eventsm.emplace_back(l, 0);
            eventsm.emplace_back(r, 1);
        }
    }
    auto handle = [](vector<pair<int,int>> &events) {
        sort(events.begin(), events.end());
        int cur = 0, mx = 0;
        for (auto &[endpoint, type]: events) {
            if (type == 0) {
                cur++;
            }
            else {
                cur--;
            }
            mx = max(mx, cur);
        }
        return mx;
    };
    int mx = max(handle(events1), handle(eventsm));
    cout << mx << '\n';
}


// void solve() {
//     int n, m;
//     cin >> n >> m;
//     vector<pair<int,int>> segs(n);
//     vector<int> vals;
//     for (auto &[l, r]: segs) {
//         cin >> l >> r;
//         vals.push_back(l);
//         vals.push_back(r);
//     }
//     vals.push_back(1);
//     vals.push_back(m);
//     sort(vals.begin(), vals.end());
//     vals.erase(unique(vals.begin(), vals.end()), vals.end());
//     auto get_idx = [&](int v) {
//         return int(lower_bound(vals.begin(), vals.end(), v) - vals.begin());
//     };
//     auto build = [&](vector<int> &d, vector<pair<int,int>> &ss) {
//         for (auto &[l, r]: ss) {
//             int lidx = get_idx(l);
//             int ridx = get_idx(r);
//             d[lidx]++;
//             d[ridx + 1]--;
//         }
//         for (int i = 1; i < int(vals.size()); i++) {
//             d[i] += d[i - 1];
//         }
//     };

//     vector<int> d(vals.size() + 1);
//     build(d, segs);

//     int mx = -1, mxidx = -1;
//     for (int i = 0; i < int(vals.size()); i++) {
//         if (d[i] > mx) {
//             mx = d[i];
//             mxidx = i;
//         }
//     }
//     vector<pair<int,int>> used;
//     for (auto &p: segs) {
//         auto &[l, r] = p;
//         int lidx = get_idx(l);
//         int ridx = get_idx(r);
//         if (lidx <= mxidx && mxidx <= ridx) {
//             used.push_back(p);
//         }
//     }
//     vector<int> ans_d(vals.size() + 1);
//     build(ans_d, used);
//     int mn = INT_MAX;
//     for (int i = 0; i < int(vals.size()); i++) {
//         mn = min(mn, ans_d[i]);
//     }
//     cout << mx - mn << '\n';
// }

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
