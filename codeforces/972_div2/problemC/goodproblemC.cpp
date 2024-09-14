#include <bits/stdc++.h>
using namespace std;

string chars = "narek";
int n, m;
vector<string> strs;
const int MAX_N = int(1e3) + 10;
int dp[MAX_N][5];
int solve_dp(int i, int curr) {
    if (i == -1) {
        return -curr;
    }

    int &ans = dp[i][curr];
    if (ans != -INT_MAX) return ans;

    int no = solve_dp(i - 1, curr);   // do not include

    int score = 0;
    for (char c: strs[i]) {
        if (c == chars[curr]) {
            curr++;
            if (curr == 5) {
                score += 5;
                curr = 0;
            }
        }
        else {
            for (int ch = 0; ch < 5; ch++) {
                if (c == chars[ch]) {
                    score--;
                    break;
                }
            }
        }
    }
    int yes = solve_dp(i - 1, curr);
    ans = max(no, yes + score);
    return ans;
}


int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        cin >> n >> m;
        strs.resize(n);
        for (int i = n - 1; i >= 0; i--) {
            cin >> strs[i];
        }
        for (int i = 0; i < n + 1; i++) {
            for (int j = 0; j < 5; j++) {
                dp[i][j] = -INT_MAX;   
            }
        }
        int ans = solve_dp(n - 1, 0);
        // for (int i = 0; i < n; i++) {
        //     for (int j = 0; j < 5; j++) {
        //         cout << dp[i][j] << " ";
        //     }
        //     cout << '\n';
        // }
        cout << ans << '\n';
    }
    return 0;
}
