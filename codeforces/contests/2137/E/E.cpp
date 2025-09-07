#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (auto &ai: a) cin >> ai;
    sort(a.begin(), a.end());
    // let's apply operation once
    vector<int> nw(n);
    int mex = 0;
    for (int i = 0; i < n; i++) {
        if ((i > 0 && a[i - 1] == a[i]) || (i + 1 < n && a[i + 1] == a[i])) {
            nw[i] = -1;
        }
        else {
            nw[i] = mex;
        }
        if (a[i] == mex) mex++;
    }
    for (int i = 0; i < n; i++) {
        if (nw[i] == -1) nw[i] = mex;
    }
    k--;
    sort(nw.begin(), nw.end());
    swap(a, nw);
    if (k == 0) {
        cout << accumulate(a.begin(), a.end(), 0LL) << '\n';
        return;
    }

    int64_t ans = 0;
    int last_good_idx = -1;
    int issue_type = 0;
    int val = -1;
    for (int i = 0; i < n; i++) {
        if (a[i] != i) {
            // found issue
            if (i == 0) {
                issue_type = 1; // missing nr
                val = i;
            }
            else {
                if (a[i] == a[i - 1]) {
                    val = a[i];
                    ans -= a[i - 1];
                    last_good_idx--;
                    issue_type = 2;   // repeated nr
                }
                else {
                    issue_type = 1;    // missing nr
                    val = i;
                }
            }
            break;
        }
        ans += a[i];
        last_good_idx = i;
    }
    int cnt_bad = n - (last_good_idx + 1);
    if (issue_type == 1) {
        // in one iteration, they go to this value
        // in two, they go to value + 1
        int64_t actual_val = k % 2 == 1 ? val : val + 1;
        ans += actual_val * cnt_bad;
    }
    else if (issue_type == 2) {
        // in one iteration, they go to val + 1
        // in two they go to val
        int actual_val = k % 2 == 1 ? val + 1 : val;
        ans += actual_val * cnt_bad;
    }
    cout << ans << '\n';
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
