#include <bits/stdc++.h>
using namespace std;

const int MAX_X = int(1e5) + 10;

vector<vector<int>> dp(MAX_X);
vector<pair<int,int>> books;
const int inf = int(1e9);

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int n, x;
    cin >> n >> x;

    books.reserve(10 * n);
    vector<int> hv(n), sv(n), kv(n);
    for (auto &a: hv) cin >> a;
    for (auto &a: sv) cin >> a;
    for (auto &a: kv) cin >> a;

    for (int i = 0; i < n; i++) {
        int h = hv[i], s = sv[i], k = kv[i];

        // BINARY DECOMPOSITION
        for (int pwr = 1; pwr < k; pwr <<= 1) {
            k -= pwr;
            int nh = pwr * h;
            int ns = pwr * s;
            books.emplace_back(nh, ns);
        }
        if (k > 0) {
            int nh = k * h;
            int ns = k * s;
            books.emplace_back(nh, ns);
        }
    }
    // for (auto &[h, s]: books) {
    //     cout << h << " " << s << endl;
    // }
    for (int i = 0; i < x; i++) {   // use <= x if do not handle the case (curr == x) in solve_dp
        dp[i].assign(books.size(), -1);
    }
    auto solve_dp = [&](int i, int curr, auto &&self) -> int {
        if (curr > x) return -inf;
        if (curr == x) return 0;
        if (i == int(books.size())) {
            return 0;
        }

        int &ans = dp[curr][i];
        if (ans != -1) return ans;

        auto &[price, pages] = books[i];

        int local = max(pages + self(i + 1, curr + price, self), self(i + 1, curr, self));
        return ans = local;
    };
    int res = solve_dp(0, 0, solve_dp);
    cout << res << '\n';
    // for (int j = 0; j < int(books.size()); j++) {

    // for (int i = 0; i <= x; i++) {
    //         cout << dp[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    return 0;
}
