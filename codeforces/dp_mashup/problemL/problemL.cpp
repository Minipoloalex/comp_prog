#include <bits/stdc++.h>
using namespace std;

int dp[1010][1010];
int p[1010][1010];

typedef pair<int, int> ii;

int main() {
    int n;
    cin >> n;
    vector<ii> groups(n);
    for (int i = 0; i < n; i++) {
        int ci, pi;
        cin >> ci >> pi;
        groups[i] = make_pair(ci, pi);
    }

    vector<int> group_inds(n);
    for (int i = 0; i < n; i++) group_inds[i] = i;

    int k;
    cin >> k;
    vector<int> tables(k);
    for (int i = 0; i < k; i++) cin >> tables[i];

    vector<int> table_inds(k);
    for (int i = 0; i < k; i++) table_inds[i] = i;

    // sort(groups.begin(), groups.end());
    // sort(tables.begin(), tables.end());
    sort(group_inds.begin(), group_inds.end(), [&](int i1, int i2) {
        if (groups[i1].first < groups[i2].first) return true;
        auto &[c1, p1] = groups[i1];
        auto &[c2, p2] = groups[i2];
        return (c1 < c2) || (c1 == c2 && p1 < p2);
    });
    sort(table_inds.begin(), table_inds.end(), [&](int i1, int i2) {
        return tables[i1] < tables[i2];
    });

    memset(p, -1, sizeof p);

    dp[0][0] = 0;
    for (int i = 0; i <= n; i++) {
        for (int ki = 0; ki <= k; ki++) {
            if (dp[i][ki] > dp[i + 1][ki]) {        // option 0
                p[i + 1][ki] = 0;
            }
            dp[i + 1][ki] = max(dp[i + 1][ki], dp[i][ki]);  // option 0

            if (dp[i][ki] > dp[i][ki + 1]) {        // option 1
                p[i][ki + 1] = 1;
            }
            dp[i][ki + 1] = max(dp[i][ki + 1], dp[i][ki]);        // option 1

            if (i >= n || ki >= k) continue;

            // auto &[ci, pi] = groups[i];
            // int curr_table_size = tables[ki];
            auto &[ci, pi] = groups[group_inds[i]];
            int curr_table_size = tables[table_inds[ki]];

            if (ci <= curr_table_size) {
                if (pi + dp[i][ki] > dp[i + 1][ki + 1]) {        // option 2
                    p[i + 1][ki + 1] = 2;
                }
                dp[i + 1][ki + 1] = max(dp[i + 1][ki + 1], pi + dp[i][ki]);        // option 2
            }
        }
    }

    int ans = dp[n][k];

    int parent = p[n][k];
    int i = n, ki = k;

    vector<ii> chosen;
    // cout << "Parents:" << '\n';
    while (parent != -1) {
        // cout << parent << " ";
        if (parent == 0) i--;
        else if (parent == 1) ki--;
        else if (parent == 2) {
            i--; ki--;
            int gr_nr = group_inds[i] + 1;
            int tab_nr = table_inds[ki] + 1;
            chosen.emplace_back(gr_nr, tab_nr);
        }
        parent = p[i][ki];
    }
    // cout << '\n';
    sort(chosen.begin(), chosen.end());

    cout << chosen.size() << " " << ans << '\n';
    for (auto &[gr, tab]: chosen) {
        cout << gr << " " << tab << '\n';
    }

    // for (i = 0; i <= n; i++) {
    //     for (ki = 0; ki <= k; ki++) {
    //         cout << p[i][ki] << " ";
    //     }
    //     cout << '\n';
    // }
    return 0;
}
