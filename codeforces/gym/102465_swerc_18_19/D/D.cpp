#include <bits/stdc++.h>
using namespace std;

void solve()
{
    int X, Y;
    cin >> X >> Y;
    int n;
    cin >> n;
    map<int, set<int>> y_to_x;
    map<int, int> y_min, y_max;

    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
 
        y_to_x[y].insert(x);

        if (y_min.find(x) == y_min.end()) y_min[x] = y;
        else y_min[x] = min(y_min[x], y);

        if (y_max.find(x) == y_max.end()) y_max[x] = y;
        else y_max[x] = max(y_max[x], y);
    }

    int64_t cnt_up = 0, cnt_down = 0;
    int64_t up = 0, down = 0;
    for (auto [_, mx] : y_max) {
        down += int64_t(mx);
        cnt_down++;
    }

    int upper = y_to_x.begin()->first;
    int64_t ans = 2 * (down - (cnt_down * upper));

    for (auto [y, xs] : y_to_x) {
        for (int x : xs) {
            if (y_min[x] == y) {
                up += y;
                cnt_up++;
            }
            if (y_max[x] == y) {
                down -= y;
                cnt_down--;
            }
        }

        int64_t cur = 2 * (down - (cnt_down * y));
        cur += 2 * ((cnt_up * y) - up);
        ans = min(ans, cur);
    }

    cout << ans + X - 1 << endl;
}

int main()
{
    cin.tie(0)->ios::sync_with_stdio(0);
    int t = 1;
    // cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}
