#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<tuple<int,int,int>> v(n);
    for (int i = 0; i < n; i++) {
        int l, r;
        cin >> l >> r;
        v[i] = make_tuple(l, r, i);
    }
    sort(v.begin(), v.end());

    vector<int> rooms(n);
    int ans = 0;
    multiset<pair<int,int>> s;
    for (auto &[l, r, initial_idx]: v) {
        int room = ans + 1; // by default, need another room
        if (!s.empty()) {
            // all inside s have earlier arrival times
            // may have conflicting departure times

            // at most, we will remove only one from the set

            int d = s.begin()->first;
            if (d < l) {    // if no conflict, we can remove and use its room
                room = rooms[s.begin()->second];    // reuse a room
                s.erase(s.begin());
            }
            // otherwise have conflict (others in the set have bigger departure time, so still conflict)
        }
        s.emplace(r, initial_idx);
        rooms[initial_idx] = room;
        ans = max(ans, room);
    }
    cout << ans << '\n';
    for (int r: rooms) cout << r << " ";
    cout << '\n';
}

void solve_coord_compression() {
    // only for the number of rooms, not the actual assignments
    int n;
    cin >> n;
    vector<pair<int,int>> c(n);
    vector<int> v;
    v.reserve(2 * n);
    for (auto &x: c) {
        cin >> x.first >> x.second;
        v.push_back(x.first);
        v.push_back(x.second);
    }
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());

    int size = int(v.size());
    vector<int> pref(size + 1, 0);
    for (int i = 0; i < size; i++) {
        auto &[l, r] = c[i];
        int lidx = int(lower_bound(v.begin(), v.end(), l) - v.begin());
        int ridx = int(lower_bound(v.begin(), v.end(), r) - v.begin());
        pref[lidx]++;
        pref[ridx + 1]--;
    }
    int ans = pref[0];
    for (int i = 1; i < size; i++) {
        pref[i] += pref[i - 1];
        ans = max(ans, pref[i]);
    }
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    solve();
    return 0;
}
