#include <bits/stdc++.h>
using namespace std;

int dp[110][1500];

int main() {
    int v1, v2, t, d;
    cin >> v1 >> v2 >> t >> d;

    memset(dp, -1, sizeof dp);
    auto func = [&](int i, int v, auto &&self) -> int {
        if (i == t - 1) {
            if (v != v2) return INT_MIN;
            return v;
        }
 
        int &ans = dp[i][v];
        if (ans != -1) return ans;

        int curr = INT_MIN;
        for (int di = -d; di <= d; di++) {
            if (v + di >= 1) {
                curr = max(curr, v + self(i + 1, v + di, self));
            }
        }
        ans = curr;
        return ans;
    };
    cout << func(0, v1, func) << '\n';

    return 0;
}
