#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<vvi> vvvi;

void solve() {
    // I did not understand how to come up with the solution (and how solution works)
    // Check editorial DP state and transitions
    // Explanation by ChatGPT:
    // https://chatgpt.com/share/6a734d92-d55c-83eb-b145-fcd7f32a61b2

    int n;
    cin >> n;
    string s;
    cin >> s;
    vvi dp(n+1, vi(n+1, INT_MAX));
    vvi ndp(n+1, vi(n+1, INT_MAX));

    dp[0][0] = 0;
    for (int i = 0; i < n; i++) { // current index
        ndp.assign(n+1, vi(n+1, INT_MAX));
        for (int f = 0; f < n; f++) { // number of Fs
            for (int sm = 0; sm < n; sm++) { // max sum
                if (dp[f][sm] == INT_MAX) continue;
                if (s[i] == 'F' || s[i] == 'N') {
                    // max sum over the current interval choice
                    // we need to maximize this to minimize the number of mistakes over all possible interval choices
                    int ncursm = sm+1;
                    int nsm = max(dp[f][sm], ncursm);

                    // want to minimize this in order to maximize the number of mistakes

                    // minimize it over all valid assignments of the first i positions
                    // that contain exactly f fake cakes and have current Kadane value cur

                    // From ChatGPT: Different partial assignments may reach the same state (i,f,cur)
                    // Among them, we prefer the one with the smallest historical maximum because
                    // the objective is f - S_max
                    ndp[f+1][ncursm] = min(ndp[f+1][ncursm], nsm);
                }
                if (s[i] == 'T' || s[i] == 'N') {
                    int ncursm = max(0, sm-1);
                    int nsm = dp[f][sm]; // ncursm is smaller for sure

                    ndp[f][ncursm] = min(ndp[f][ncursm], nsm);
                }
            }
        }
        swap(ndp, dp);
    }
    int ans = 0;
    for (int f = 0; f <= n; f++) {
        for (int sm = 0; sm <= n; sm++) {
            if (dp[f][sm] != INT_MAX) {
                ans = max(ans, f - dp[f][sm]);
            }
        }
    }
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
