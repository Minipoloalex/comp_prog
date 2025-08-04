#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for (auto &ai: a) cin >> ai;
    for (auto &bi: b) cin >> bi;
    auto simulate = [&](int i) {
        int x = a[i], y = b[i];
        if (x == 0 && y == 0) return -1;
        if (x == 0) return 0;
        if (y == 0) return 1;

        int g = gcd(x, y);
        x /= g;
        y /= g;
        if (x % 2 == 1 && y % 2 == 1) {
            return 2;
        }
        else if (x % 2 == 1 && y % 2 == 0) {
            return 1;
        }
        else if (x % 2 == 0 && y % 2 == 1) {
            return 0;
        }
        exit(1);
    };
    auto simulate_v2 = [&](int i) { // another solution
        int x = a[i], y = b[i];
        if (x == 0 && y == 0) return -1;
        if (x == 0) return 0;
        if (y == 0) return 1;
        int ans = 2;
        if (x < y) {
            tie(x, y) = make_pair(y, y - x);
            ans++;
        }
        while (y) {
            int k = x / y;
            int r = x - k * y;
            
            ans += (k - 1) / 2 * 3;
            if (k % 2 == 0) {
                ans++;
                x = r + y;
            }
            else {
                x = y;
            }
            y = r;
            if (y > 0) ans++;
        }
        return ans % 3;
    };
    bool ans = true;
    int mod = -1;
    for (int i = 0; i < n; i++) {
        int cur = simulate(i);
        if (cur == -1) continue;
        if (mod == -1) {
            mod = cur;
        }
        else if (cur != mod) {
            ans = false;
        }
    }
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
