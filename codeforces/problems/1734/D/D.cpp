#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int64_t> a(n + 2);
    for (int i = 1; i <= n; i++) cin >> a[i];
    bool ans = false;
    int64_t hp = a[k];
    int l = k - 1, r = k + 1;
    int leftpointer, rightpointer;
    int64_t leftadd, rightadd, leftneed, rightneed;
    bool computedleft = false, computedright = false;
    while (l >= 1 && r <= n) {
        if (!computedleft) {
            int64_t cur = 0, total = 0, mn = 0;
            int i;
            for (i = l; i >= 1 && total <= 0; i--) {
                cur += a[i];
                total += a[i];
                if (cur > 0) cur = 0;
                mn = min(mn, cur);
            }
            leftpointer = i;
            leftadd = total;
            leftneed = mn;
            computedleft = true;
        }
        if (!computedright) {
            int64_t cur = 0, total = 0, mn = 0;
            int i;
            for (i = r; i <= n && total <= 0; i++) {
                cur += a[i];
                total += a[i];
                if (cur > 0) cur = 0;
                mn = min(mn, cur);
            }
            rightpointer = i;
            rightadd = total;
            rightneed = mn;
            computedright = true;
        }
        if (hp >= abs(leftneed)) {
            l = leftpointer;
            hp += leftadd;
            computedleft = false;
        }
        else if (hp >= abs(rightneed)) {
            hp += rightadd;
            computedright = false;
            r = rightpointer;
        }
        else {
            break;
        }
    }
    if (l == 0 || r == n + 1) ans = true;
    cout << (ans ? "YES" : "NO") << '\n';
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
