#include <bits/stdc++.h>
using namespace std;

void solve() {
    freopen("convention2.in", "r", stdin);
    freopen("convention2.out", "w", stdout);
    int n;
    cin >> n;
    vector<tuple<int,int,int>> cows(n);
    for (int i = 0; i < n; i++) {
        int ai, ti;
        cin >> ai >> ti;
        cows[i] = make_tuple(ai, i, ti);    // sort by i (seniority) for same ai
    }
    sort(cows.begin(), cows.end());

    set<pair<int,int>> s;   // priority queue
    int ans = 0, prev_departure = 0;
    for (int i = 0; i < n; i++) {
        // cout << i << " " << prev_departure << endl;
        auto &[ai, initial_idx, ti] = cows[i];
        if (prev_departure < ai) {
            while (!s.empty() && prev_departure < ai) {
                // get cow with highest seniority
                auto &[sen_idx, sen_curr_idx] = *s.begin();
                s.erase(s.begin());

                auto &[sen_cow_ai, _, sen_cow_ti] = cows[sen_curr_idx];

                ans = max(ans, prev_departure - sen_cow_ai);
                prev_departure = prev_departure + sen_cow_ti;
            }
            if (s.empty()) {
                prev_departure = ai + ti;
            }
            else {
                s.emplace(initial_idx, i);
            }
        }
        else {
            assert(prev_departure >= ai);
            s.emplace(initial_idx, i);
        }
    }

    while (!s.empty()) {
        auto &[sen_idx, sen_curr_idx] = *s.begin();
        s.erase(s.begin());
        auto &[sen_cow_ai, _, sen_cow_ti] = cows[sen_curr_idx];
        ans = max(ans, prev_departure - sen_cow_ai);
        prev_departure = prev_departure + sen_cow_ti;
    }
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    solve();
    return 0;
}
