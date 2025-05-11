#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    vector<int> mp(n + 1, -1);
    vector<int> evens, odds;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        mp[a[i]] = i;
        if (i & 1) odds.push_back(a[i]);
        else evens.push_back(a[i]);
    }
    auto swap_stuff = [&](int i, int j) {
        swap(mp[a[i]], mp[a[j]]);
        swap(mp[a[i + 1]], mp[a[j + 1]]);
        swap(a[i], a[j]);
        swap(a[i + 1], a[j + 1]);
    };
    sort(odds.begin(), odds.end());
    sort(evens.begin(), evens.end());

    int i = 0;
    for (int j = 0; j <= n - 4; j++) {
        if (j % 2 == 0) {
            int x = evens[i];
            int &xidx = mp[x];
            if (xidx == n - 1) {
                swap_stuff(n - 4, n - 2);
            }
            if (xidx != j) {
                swap_stuff(j, xidx);
            }
        }
        else {
            int x = odds[i];
            int &xidx = mp[x];
            if (xidx == n - 1) {
                swap_stuff(n - 4, n - 2);
            }
            if (xidx != j) {
                swap_stuff(j, xidx);
            }
            i++;
        }
    }

    for (i = 0; i < n; i++) {
        cout << a[i] << " \n"[i == n - 1];
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
