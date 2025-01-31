#include <bits/stdc++.h>
using namespace std;

char chars[] = "narek";

int n, m;
vector<string> strs;

const int MAX_N = int(1e3) + 10;
const int MAX_M = MAX_N;
int dp[MAX_N][5];

bool wanted_char[MAX_N][MAX_M];
pair<int, int> other_dp[MAX_N][5];

void solve_other_dp() {
    for (int i = 0; i < n; i++) {
        string &s = strs[i];
        for (int ch = 0; ch < 5; ch++) {
            int curr = ch;
            int score = 0;
            for (int j = 0; j < m; j++) {
                if (s[j] == chars[curr]) {
                    curr++;
                    if (curr == 5) {
                        score += 5;
                        curr = 0;
                    }
                }
                else {
                    score -= wanted_char[i][j];
                    // for (int ch = 0; ch < 5; ch++) {
                    //     if (c == chars[ch]) {
                    //         score--;
                    //         break;
                    //     }
                    // }
                }
            }
            other_dp[i][ch] = make_pair(score, curr);
        }
    }
}


int solve_dp(int i, int curr) {
    if (i == -1) {
        return -curr;
    }

    int &ans = dp[i][curr];
    if (ans != -INT_MAX) return ans;

    // cout << i << " ";

    int no = solve_dp(i - 1, curr);   // do not include
    // int score = 0;
    // string &s = strs[i];
    auto &[score, ncurr] = other_dp[i][curr];

    // for (int j = 0; j < m; j++) {
    //     if (s[j] == chars[curr]) {
    //         curr++;
    //         if (curr == 5) {
    //             score += 5;
    //             curr = 0;
    //         }
    //     }
    //     else {
    //         score -= wanted_char[i][j];
    //         // for (int ch = 0; ch < 5; ch++) {
    //         //     if (c == chars[ch]) {
    //         //         score--;
    //         //         break;
    //         //     }
    //         // }
    //     }
    // }
    int yes = solve_dp(i - 1, ncurr);

    dp[i][curr] = max(no, yes + score);
    return dp[i][curr];
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
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                wanted_char[i][j] = 0;
                for (char ch: chars) {
                    if (strs[i][j] == ch) {
                        wanted_char[i][j] = 1;
                        break;
                    }
                }
            }
        }
        for (int i = 0; i < n + 1; i++) {
            for (int j = 0; j < 5; j++) {
                dp[i][j] = -INT_MAX;
            }
        }
        solve_other_dp();
        // cout << "HELLO " << n << endl;
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
