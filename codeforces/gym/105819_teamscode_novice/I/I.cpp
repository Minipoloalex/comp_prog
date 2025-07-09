#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<pair<int,int>> houses(n);
    for (auto &[l, r]: houses) {
        int row, col;
        cin >> row >> col;
        l = col;
        r = row + col;
    }
    sort(houses.begin(), houses.end(), [&](pair<int,int> &p1, pair<int,int> &p2) {
        auto &[l1, r1] = p1;
        auto &[l2, r2] = p2;
        int s1 = r1 - l1;
        int s2 = r2 - l2;
        return l1 < l2 || (l1 == l2 && s1 > s2);
    });
    int cost = 0;    // max is 2e9
    int lst = 0, cnt = 0;
    vector<int> spaces;
    for (auto &[l, r]: houses) {
        if (lst >= r) continue;
        if (l <= lst) {
            // "merge" with previous interval
            cost += r - lst;
            lst = r;
        }
        else {
            cnt++;
            // create a new interval (if not the first, then creates a space in between intervals)
            if (lst != 0) {
                int space = l - lst;
                assert(space >= 0);
                if (space > 0) {
                    spaces.push_back(space); // space in between the intervals: (lst, l)
                }
            }
            cost += r - l;
            lst = r;
        }
    }
    sort(spaces.begin(), spaces.end());
    vector<int> ans(n + 1);
    for (int i = cnt; i <= n; i++) {
        ans[i] = cost;
    }

    for (int i = cnt - 1, j = 0; i >= 1; i--, j++) {
        cost += spaces[j];
        ans[i] = cost;
    }
    for (int i = 1; i <= n; i++) cout << ans[i] << " ";
    cout << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
