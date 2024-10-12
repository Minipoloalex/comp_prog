#include <bits/stdc++.h>
using namespace std;

constexpr int MOD = int(1e9) + 7;

int power_mod(int a, int64_t b) {
    if (b == 0) return 1;

    int r = power_mod(a, b / 2);

    if (b % 2 == 0) return int((1LL * r * r) % MOD);
    return int(1LL * (1LL * r * r % MOD) * a % MOD);
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int n, x;
    cin >> n >> x;
    int64_t sum = 0;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        sum += a[i];
    }

    map<int64_t, int> cnt;
    for (int i = 0; i < n; i++) {
        cnt[sum - a[i]]++;
    }
    int64_t curr = sum - a.back();
    while (cnt[curr] % x == 0) {
        // e.g. cnt[curr] = 10 * x (with x = 5); 10 * x ^ curr; cnt[curr + 1] = 2; 2 * x ^ (curr + 1)
        cnt[curr + 1] += cnt[curr] / x;
        curr++;
    }
    if (curr > sum) curr = sum;
    int ans = power_mod(x, curr);
    cout << ans << '\n';
    return 0;
}
