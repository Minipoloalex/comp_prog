#include <bits/stdc++.h>
using namespace std;

#define sz(v) int((v).size())

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> ps(n+1);
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        ps[y].push_back(x);
    }
    vector<int64_t> S(n+1), mn(n+1);
    int64_t cursm = 0;
    priority_queue<int,vector<int>,greater<int>> pq; // min queue
    for (int i = n; i >= 0; i--) {
        // there can be i+1 particles
        int mx_sz = i + 1;
        while (sz(pq) > mx_sz) {
            cursm -= pq.top();
            pq.pop();
        }
        for (int y: ps[i]) {
            if (sz(pq) < mx_sz || y > pq.top()) {
                if (sz(pq) == mx_sz) {
                    cursm -= pq.top();
                    pq.pop();
                }
                pq.push(y);
                cursm += y;
            }
        }
        S[i] = cursm;
        mn[i] = sz(pq) == mx_sz ? pq.top() : 0;
    }
    int64_t M = *max_element(S.begin(), S.end());

    vector<pair<int,int>> b(m);
    for (auto &[x, y]: b) cin >> x >> y;

    vector<vector<int>> bid(n+1);
    for (int j = 0; j < m; j++) {
        auto &[x, y] = b[j];
        bid[y].push_back(j);
    }
    vector<int64_t> ans(m);
    int64_t cur_mx = 0;
    for (int i = 0; i <= n; i++) {
        cur_mx = max(cur_mx, S[i] - mn[i]);
        for (int j: bid[i]) {
            int x = b[j].first;
            ans[j] = max(M, cur_mx + x);
        }
    }
    for (auto &x: ans) cout << x << " ";
    cout << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
