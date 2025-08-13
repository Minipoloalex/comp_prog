#include <bits/stdc++.h>
using namespace std;

double rec_pow(double prob_happy, double p, int n) {
    if (n == 0) return prob_happy;
    if (n & 1) {
        return rec_pow(prob_happy * (1 - p) + (1 - prob_happy) * p, p, n - 1);
    }
    return rec_pow(prob_happy, p * (1 - p) + (1 - p) * p, n / 2);
}

void solve() {
    int n;
    cin >> n;
    double p;
    cin >> p;
    double ans = 1;
    while (n) {
        if (n & 1) {
            // not happy and switches or happy and doesn't switch
            ans = p * (1 - ans) + (1 - p) * ans;
            n--;
        }
        p = p * (1 - p) + (1 - p) * p;
        n >>= 1;
    }
    // double ans = rec_pow(1, p, n);
    cout << fixed << setprecision(10) << ans << '\n';
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
