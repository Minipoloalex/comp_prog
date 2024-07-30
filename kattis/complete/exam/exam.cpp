#include <bits/stdc++.h>
using namespace std;

int dp[1010][1010];

int main() {
    int k;
    cin >> k;
    string f, m;
    cin >> f >> m;
    int n = (int) f.size();

    // string dp solution

    // for (int ki = 0; ki <= k; ki++) dp[0][ki] = 0;
    dp[0][0] = 0;
    for (int i = 0; i < n; i++) {
        for (int ki = 0; ki <= k && ki <= i; ki++) {
            dp[i + 1][ki] = max(dp[i + 1][ki], dp[i][ki] + (m[i] == f[i] ? 0 : 1)); // friend not correct
            dp[i + 1][ki + 1] = max(dp[i + 1][ki + 1], dp[i][ki] + (m[i] == f[i] ? 1 : 0)); // friend correct
        }
    }
    cout << dp[n][k] << '\n';
    return 0;
}
