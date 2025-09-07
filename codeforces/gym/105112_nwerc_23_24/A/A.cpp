#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, s;
    cin >> n >> s;
    vector<int> w(n);
    for (auto &wi: w) cin >> wi;
    sort(w.begin(), w.end());
    if (n == 1 || s == 1) {
        cout << "1\n";
        return;
    }
    n -= 2;

    int cnt1 = 0, cnt2 = 0;
    int occ = 2;

    int ans = 2;
    for (int i = 0; i < n; i++) {
        occ += w[i] / 3;
        if (w[i] % 3 == 2) {
            if (cnt1 > 0) {
                cnt1--;
            }
            else {
                cnt2++;
                occ++;
            }
        }
        else if (w[i] % 3 == 1) {
            if (cnt2 > 0) {
                cnt2--;
            }
            else {
                cnt1++;
                occ++;
            }
        }
        while (occ > s && cnt1 >= 2) {
            occ--;
            cnt1 -= 2;
        }
        if (occ <= s) {
            ans++;
        }
        else {
            break;
        }
    }
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
