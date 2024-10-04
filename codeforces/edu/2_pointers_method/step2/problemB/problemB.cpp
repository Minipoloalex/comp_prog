#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; int64_t s;
    cin >> n >> s;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    int l = 0, r = 0;
    int best = INT_MAX;
    int64_t curr_sum = 0;
    while (l < n && r <= n) {
        if (curr_sum >= s) {
            curr_sum -= a.at(l++);
        }
        else {
            if (r == n) break;
            curr_sum += a.at(r++);
        }
        if (curr_sum >= s) {
            best = min(best, r - l);
        }
    }

    if (best == INT_MAX) best = -1;
    cout << best << '\n';
    return 0;
}
