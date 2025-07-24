#include <bits/stdc++.h>
using namespace std;

vector<int64_t> digits(int64_t x) {
    vector<int64_t> ans;
    while (x) {
        int64_t d = x % 2;
        x /= 2;
        ans.push_back(d);
    }
    reverse(ans.begin(), ans.end());
    return ans;
}
int64_t value(const vector<int64_t> &digits) {
    int64_t ans = 0;
    for (int64_t d: digits) {
        ans <<= 1;
        ans |= d;
    }
    return ans;
}

void solve() {
    int64_t x;
    cin >> x;
    if (__builtin_popcountll(x) == 1 && x != 1) {
        cout << x - 1 << '\n';
        return;
    }
    vector<int64_t> ds = digits(x);
    int n = int(ds.size());
    for (int i = 0; i < n / 2; i++) {
        ds[n - i - 1] = ds[i];
    }
    int64_t new_x = value(ds);
    int64_t ans;
    if (new_x <= x) {
        ans = new_x;
    }
    else {
        for (int i = (n % 2 == 0 ? n / 2 - 1 : n / 2); i >= 0; i--) {
            if (ds[i] == 1) {
                ds[i] = 0;
                ds[n - 1 - i] = 0;
                break;
            }
            else {
                ds[i] = 1;
                ds[n - 1 - i] = 1;
            }
        }
        ans = value(ds);
    }
    if (ans == 0) ans = 1;
    assert(ans <= x);
    cout << ans << '\n';
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
