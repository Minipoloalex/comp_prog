#include <bits/stdc++.h>
using namespace std;

#define sz(v) int((v).size())

void solve() {
    int n, k, x, y;
    cin >> n >> k >> x >> y;
    vector<pair<int,char>> st(n);
    for (auto &[s,c]: st) {
        cin >> c >> s;
    }
    sort(st.rbegin(), st.rend());
    using PQ = priority_queue<int,vector<int>,greater<int>>;
    int always_use = -1;
    array<PQ,2> p = {PQ{}, PQ{}};
    for (int i = 0; i < n; i++) {
        auto [skill, ch] = st[i];
        int want = ch - 'A';
        int to_use = always_use == -1 ? want : always_use;
        PQ &pq = p[to_use];

        int actual_skill = skill;
        if (want == 0 && to_use == 1) {
            actual_skill -= x;
        }
        if (want == 1 && to_use == 0) {
            actual_skill -= y;
        }

        if (sz(pq) < k) {
            pq.push(actual_skill);
        }
        else {
            int worst = pq.top();    // assuming a min heap
            if (worst < actual_skill) {
                pq.pop();
                pq.push(actual_skill);
            }
        }

        if (always_use == -1 && sz(pq) == k) {
            always_use = 1 - want;
        }
    }
    int64_t ans = 0;
    for (int i = 0; i < 2; i++) {
        while (!p[i].empty()) {
            int sk = p[i].top();
            p[i].pop();
            ans += sk;
        }
    }
    cout << ans << '\n';
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
