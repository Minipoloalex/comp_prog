#include <bits/stdc++.h>
using namespace std;

void solve() {
    int64_t l, r, g;
    cin >> l >> r >> g;
    int64_t rightmost = r / g * g;
    int64_t leftmost = l / g * g;
    if (leftmost < l) {
        leftmost += g;
    }
    if (l <= leftmost && leftmost <= r && l <= rightmost && rightmost <= r) {
        leftmost /= g;
        rightmost /= g;
        int64_t lef = -1, rig = -1;
        for (int64_t d = rightmost - leftmost; d >= 0; d--) {
            for (int64_t i = leftmost; i + d <= rightmost; i++) {
                int64_t curl = i, curr = i + d;
                if (gcd(curl, curr) == 1) {
                    lef = curl * g;
                    rig = curr * g;
                    goto end;
                }
            }
        }
        end:
        cout << lef << " " << rig << '\n';
    }
    else {
        cout << "-1 -1\n";
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
