#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef pair<int, int> ii;
vi ms, ns;
ii dp[4005][4005];


int main() {
    int m, n, x, y;
    cin >> m;
    ms.resize(m);
    for (int i = 0; i < m; i++) {
        cin >> x >> y;
        ms[i] = x * 1000 + y;
    }
    cin >> n;
    ns.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> x >> y;
        ns[i] = x * 1000 + y;
    }

    for (int ni = 0; ni <= n; ni++) {
        dp[ni][0] = make_pair(0, 1);
    }
    for (int mi = 0; mi <= m; mi++) {
        dp[0][mi] = make_pair(0, 1);
    }
    for (int ni = 1; ni <= n; ni++) {
        int nval = ns[ni - 1];
        for (int mj = 1; mj <= m; mj++) {
            int mval = ms[mj - 1];
            ii diag = dp[ni - 1][mj - 1];
            ii left = dp[ni - 1][mj];
            ii top = dp[ni][mj - 1];

            // dp[ni][mj] = make_pair(0, 0);
            if (nval == mval) {
                int nlen = diag.first + 1;
                if (nlen > left.first && nlen > top.first) {
                    dp[ni][mj] = make_pair(nlen, diag.second);
                }
                else if (nlen == left.first && nlen == top.first) {
                    dp[ni][mj] = make_pair(nlen, left.second + top.second + diag.second);
                }
                else if (nlen == left.first) {
                    dp[ni][mj] = make_pair(nlen, diag.second + left.second);
                }
                else if (nlen == top.first) {
                    dp[ni][mj] = make_pair(nlen, diag.second + top.second);
                }
                else while(1);

            }
            else {
                if (diag.first == left.first and diag.first == top.first) {
                    dp[ni][mj] = make_pair(diag.first, left.second + top.second - diag.second);
                }
                else if (left.first > top.first) {
                    dp[ni][mj] = make_pair(left.first, left.second);
                }
                else if (top.first > left.first) {
                    dp[ni][mj] = make_pair(top.first, top.second);   
                }
                else if (top.first == left.first) {
                    dp[ni][mj] = make_pair(top.first, top.second + left.second);
                }
                else while(1);
            }
        }
    }
    // cout << "\t\t";
    // for (int mj = 0; mj < m; mj++) {
    //     cout << ms[mj] << '\t';
    // }
    // cout << endl;
    // for (int ni = 0; ni <= n; ni++) {
    //     if (ni > 0) {
    //         cout << ns[ni - 1] << '\t';
    //     }
    //     else {
    //         cout << '\t';
    //     }
    //     for (int mj = 0; mj <= m; mj++) {
    //         cout << "(" << dp[ni][mj].first << ", " << dp[ni][mj].second << ")\t";
    //     }
    //     cout << endl;
    // }
    if (dp[n][m].first == 0) {
        cout << "no connection found" << '\n';
    }
    else {
        cout << dp[n][m].first << " " << dp[n][m].second << '\n';
    }
    return 0;
}
