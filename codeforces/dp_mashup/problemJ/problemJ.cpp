#include <bits/stdc++.h>
using namespace std;


int64_t dp[100010][10][3];

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> el(n, vector<int>());
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        el[u].push_back(v);
        el[v].push_back(u);
    }

    int k, x;
    cin >> k >> x;

    int mod = int(1e9) + 7;

    vector<bool> vis(n, 0);

    auto func = [&](int i, int left, int flag, auto &&self) -> int64_t {
        // flag -> 0 (< k), 1 (== k), 2 (> k)

        vis[i] = 1;

        int64_t &ans = dp[i][left][flag];
        if (ans != -1) return ans;

        int64_t curr = 1;   // consider base case (leaves)
        for (int v: el[i]) {
            if (!vis[v]) {  // start from root, go lower -> want to use not visited nodes
                // int nleft, nflag;
                // int64_t c = self(v, nleft, nflag, self);

                // curr *= number of possible numbers here
                int64_t val;
                int64_t numbers;
                if (flag == 0) {
                    // use values < k here (can use anything on others)
                    // others use: k, < k, > k
                    val = self(v, left - 1, 0, self) + self(v, left, 0, self) 
                    + self(v, left, 2, self);
                    numbers = -1;
                }
                else if (flag == 1) {
                    // use value == k here (can only use < k on others)
                    if (left == 0) val = 0;
                    else val = self(v, left - 1, 0, self);
                    numbers = -1;
                }
                else {  // flag == 2
                    // use values > k here (can use any values except k on others)
                    val = self(v, left, 0, self) + self(v, left, 2, self);
                    numbers = -1;
                }

                curr *= val * numbers;
            }
        }
        ans = curr;
        return ans;
    };

    // initial_flag = 2 (less restrictions)
    cout << func(0, x, 2, func) << '\n';

    return 0;
}
