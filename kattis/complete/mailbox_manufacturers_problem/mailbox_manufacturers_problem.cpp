#include <bits/stdc++.h>
using namespace std;

#define INF 1e9

int memo[11][101][101];

// s should never be 0, but e can be equal to m
// Do not have any information in [s, e], including s and e
// otherwise, know values < s do not explode and values > e explode
int dp(int k, int s, int e) {
    if (s > e) return 0;
    if (memo[k][s][e] != -1) return memo[k][s][e];
    if (k == 1) return (e*(e + 1) - s*(s-1)) / 2;
    if (s == e) return s;
    int best_val = INF;
    for (int i = s; i <= e; i++) {
        // K - 1 -> explosion, go left (use less)
        // K -> no explosion, go right (use more)
        int val = max(dp(k - 1, s, i - 1) + i, dp(k, i + 1, e) + i);
        if (val < best_val) {
            best_val = val;
        }
    }
    return memo[k][s][e] = best_val;
}

int main() {
    // k [1, 10] identical prototypes
    // m [1, 100] crackers
    memset(memo, -1, sizeof memo);
    int t; cin >> t;
    while (t--) {
        int k, m;
        cin >> k >> m;
        cout << dp(k, 1, m) << endl;
    }
    return 0;
}
