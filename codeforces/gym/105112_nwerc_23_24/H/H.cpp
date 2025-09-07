#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    vector<int> cnt(3);
    vector<vector<int>> ans;

    for (auto &ai: a) {
        cin >> ai;
        if (ai <= 2) {
            cnt[ai]++;
        }
    }
    if (n == 1) {
        cout << a[0] << '\n';
        return;
    }
    if (cnt[1] == n) {
        vector<int> ones;
        for (int i = 0; i < min(n, 3); i++) {
            ones.push_back(1);
        }
        cnt[1] -= int(ones.size());
        ans.push_back(ones);
    }
    sort(a.rbegin(), a.rend());
    for (int i = 0; i < n; i++) {
        if (a[i] <= 2) {
            break;
        }
        ans.push_back({a[i]});
    }

    while (cnt[1] > 0 && cnt[2] > 0) {
        // combine 1s with 2s while we can
        // since they duplicate while using only one 1
        ans.push_back({1,2});
        cnt[1]--;
        cnt[2]--;
    }

    while (cnt[2] > 0) {
        ans.push_back({2}); // no more 1s, but still have 2s
        cnt[2]--;
    }

    while (cnt[1] >= 3) {
        ans.push_back({1,1,1});
        cnt[1] -= 3;
    }

    if (cnt[1] == 1) {
        assert(!ans.empty());
        ans.back().push_back(1); // on the smallest
    }
    else if (cnt[1] == 2) {
        ans.push_back({1,1});
    }

    for (int j = 0; j < int(ans.size()); j++) {
        auto &v = ans[j];
        cout << '(';
        for (int i = 0; i < int(v.size()); i++) {
            cout << v[i];
            if (i < int(v.size()) - 1) {
                cout << '+';
            }
        }
        cout << ')';
        if (j < int(ans.size()) - 1) {
            cout << '*';  
        }
        else {
            cout << '\n';
        }
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
