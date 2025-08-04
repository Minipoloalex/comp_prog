#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &ai: a) cin >> ai;
    vector<int> asc(n), desc(n);
    asc[n - 1] = desc[n - 1] = n - 1;
    for (int i = n - 2; i >= 0; i--) {
        if (a[i] < a[i + 1]) {
            asc[i] = asc[i + 1];
            desc[i] = i;
        }
        else if (a[i] > a[i + 1]) {
            asc[i] = i;
            desc[i] = desc[i + 1];
        }
        else {
            asc[i] = desc[i] = i;
        }
    }
    vector<array<int,2>> dp(n, {-1,-1});
    function<int(int,int)> go = [&](int i, int ispos) {
        if (i == n) return 0;

        int &ans = dp[i][ispos];
        if (ans != -1) return ans;

        int cur = 0;
        // use ascending: positive values
        cur = go(asc[i] + 1, 1) + (ispos == 1);

        if (!ispos) {
            // editorial solution uses same principle (prefix is negative)
            // but uses with prefix and suffix sums (it's a more "greedy" solution)

            // can use negatives as well
            cur = min(cur, go(desc[i] + 1, 0) + 1);
        }
        return ans = cur;
    };
    int ans = go(0, 0);
    cout << ans << '\n';
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
