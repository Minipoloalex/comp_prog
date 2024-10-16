#include <bits/stdc++.h>
using namespace std;

int64_t dp[250];

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int D;
    cin >> D;
    vector<int> primes;
    const int MAX = D + 1;
    for (int i = 2; i < MAX; i++) {
        bool is_prime = true;
        for (int p: primes) {
            if (i % p == 0) is_prime = false;
        }
        if (is_prime) primes.push_back(i);
    }
    // for (int p: primes) cout << p << " ";
    // cout << endl;

    int n = int(primes.size());
    memset(dp, 0, sizeof(dp));

    dp[0] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (primes[i] + 14 >= primes[j]) {
                dp[j] += dp[i];
            }
        }
    }
    cout << dp[n - 1] << '\n';
    return 0;
}
