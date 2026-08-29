#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;
    bool yes = m <= n / 2;
    vector<pair<int,int>> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].first;
        a[i].second = i+1;
    }
    sort(a.begin(), a.end());
    vector<pair<int,int>> ans; ans.reserve(n);
    if (yes) {
        if (m == 0) {
            vector<pair<int,int>> aux; aux.reserve(n);
            int h = a.back().first;
            int cur = n-2;
            while (h > 0 && cur >= 0) {
                aux.emplace_back(a[cur].second, a[n-1].second);
                h -= a[cur].first;
                cur--;
            }
            if (h > 0) {
                yes = false;
            }
            else {
                swap(aux.back().first, aux.back().second);
                // cur: [-1, n-2]
                for (int i = 0; i <= cur; i++) {
                    ans.emplace_back(a[i+1].second, a[i].second);
                }
                ans.insert(ans.end(), aux.begin(), aux.end());
            }
        }
        else {
            int lst = m*2;
            int rem = n;
            int i = 0;
            while (rem > lst) {
                ans.emplace_back(a[i+1].second, a[i].second);
                i++;
                rem--;
            }
            assert(rem == lst);
            for (int j = i; j < n; j += 2) {
                ans.emplace_back(a[j+1].second, a[j].second);
            }
        }
    }
    if (yes) {
        cout << ans.size() << '\n';
        for (auto &[x, y]: ans) {
            cout << x << " " << y << '\n';
        }
    }
    else {
        cout << "-1\n";
    }
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
