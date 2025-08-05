#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<pair<int,int>> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].first;
        a[i].second = i;
    }
    sort(a.begin(), a.end());
    bool ans = true;
    vector<int> b(n);
    int l = 0, r = n - 1;
    int cur = n;
    while (l <= r && ans) {
        int cnt_on_the_right_of_r = n - 1 - r;
        int cnt_current_values_middle = r - l + 1;
        if (a[l].first == cnt_on_the_right_of_r) {
            b[a[l].second] = -cur;
            cur--;
            l++;
        }
        else if (a[r].first == cnt_on_the_right_of_r + cnt_current_values_middle) {
            b[a[r].second] = cur;
            cur--;
            r--;
        }
        else {
            ans = false;
        }
    }
    if (ans) {
        cout << "YES\n";
        for (int i = 0; i < n; i++) {
            assert(b[i] != 0);
            cout << b[i] << " ";
        }
        cout << '\n';
    }
    else {
        cout << "NO\n";
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
