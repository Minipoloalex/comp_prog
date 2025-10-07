#include <bits/stdc++.h>
using namespace std;

const int MAX = int(2e5);
typedef pair<int64_t,int64_t> ii;

ii get_best(ii a, ii b) {
    if (b.first == -1 && b.second == -1) {
        return a;
    }
    int64_t lef = a.first * b.second;
    int64_t rig = a.second * b.first;
    if (lef > rig) {
        return a;
    }
    return b;
}

void solve() {
    int n;
    cin >> n;
    vector<vector<int>> msgs(MAX);
    for (int i = 0; i < n; i++) {
        int mi, ki;
        cin >> mi >> ki;
        mi--;
        msgs[mi].push_back(ki);
    }
    vector<pair<int,int>> sortedmsgs(MAX);
    auto mysort = [&](int x) {
        for (int i = 0; i < MAX; i++) {
            int val = 0;
            for (int k: msgs[i]) {
                val += min(k, x);
            }
            sortedmsgs[i] = {val, i};
        }
        sort(sortedmsgs.rbegin(), sortedmsgs.rend());

        int64_t ans = 0;
        for (int i = 0; i < x; i++) ans += sortedmsgs[i].first;
        return ans;
    };

    pair<int64_t,int64_t> best = {-1,-1};
    int64_t cur = 0;
    for (int i = 1; i <= 20; i++) {
        cur = mysort(i);
        best = get_best({cur, i}, best);
    }
    for (int i = 21; i <= MAX; i++) {
        cur += sortedmsgs[i].first;
        best = get_best({cur, i}, best);
    }
    mysort(best.second);
    cout << best.second << '\n';
    for (int i = 0; i < best.second; i++) {
        cout << sortedmsgs[i].second + 1 << " \n"[i == best.second - 1];
    }
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
