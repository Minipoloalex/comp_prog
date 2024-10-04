#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    int64_t s;
    cin >> n >> s;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    int best = 0;
    int64_t curr_sum = 0;
    int l = 0, r = 0;
    while (l < n && r <= n) {
        // cout << l << " " << r << " " << curr_sum << endl;
        if (curr_sum > s) {
            curr_sum -= a.at(l++);
        }
        else {
            if (r == n) break;  // no more elements
            curr_sum += a.at(r++);
        }
        if (curr_sum <= s) {
            best = max(best, r - l);
        }
    }
    cout << best << '\n';
    return 0;
}
