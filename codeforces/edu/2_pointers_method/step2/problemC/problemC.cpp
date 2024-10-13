#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int n;
    int64_t s;
    cin >> n >> s;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int64_t ans = 0, curr_sum = 0;
    for (int l = 0, r = 0; r < n; ) {
        curr_sum += a.at(r++);
        while (curr_sum > s && l < n) {
            curr_sum -= a.at(l++);
        }
        if (curr_sum <= s) {
            ans += r - l;
        }
    }
    cout << ans << '\n';
    return 0;
}
