#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    int swf = 0, swl;

    int count0s = 0;
    for (swl = swf; swl < n; swl++) {   // calculate intial values for swf and swl
        if (a[swl] == 0) {
            if (count0s < k) count0s++;
            else break;
        }
    }
    // cout << swf << " " << swl << '\n';

    int ans = swl - swf;
    int ans_swf = swf, ans_swl = swl;

    int prev_swf = swf;
    swf++;
    for ( ; swf < n && swl < n; swf++) {    // loop through array considering each index as swf
        // if prev_swf is a 1, cannot add anything at the end

        if (a[prev_swf] == 0) {
            // lost a 0, can add a 0 and possibly more 1s right after that 0
            count0s = k - 1;
            while (swl < n) {
                if (a[swl] == 0) {
                    if (count0s < k) count0s++;
                    else break;
                }
                swl++;
            }

            int curr = swl - swf;
            if (curr > ans) {
                ans = curr;
                ans_swf = swf;
                ans_swl = swl;
            }
        }
        prev_swf = swf;
        // cout << swf << " " << swl << '\n';
    }

    cout << ans << '\n';
    for (int i = 0; i < n; i++) {
        if (i >= ans_swf && i < ans_swl) {
            cout << 1 << " ";
        }
        else cout << a[i] << " ";
    }
    cout << '\n';
    return 0;
}
