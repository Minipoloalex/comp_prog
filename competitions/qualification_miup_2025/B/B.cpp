#include <bits/stdc++.h>
using namespace std;

void solve() {
    vector<vector<int>> dices(3, vector<int>(6));
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 6; j++) {
            cin >> dices[i][j];
        }
        sort(dices[i].begin(), dices[i].end());
    }
    auto all_equal = [&](int i, int j) {
        set<int> one(dices[i].begin(), dices[i].end());  
        return one.size() == 1 && dices[j] == dices[i];
    };
    auto good = [&](int i, int j) {
        int nr = 0;
        for (int k = 0; k < 6; k++) {
            for (int u = 0; u < 6; u++) {
                if (dices[i][k] > dices[j][u]) nr++;
            }
        }
        // cout << i << " " << j << " " << nr << endl;
        return nr;
    };
    int res = INT_MAX;
    for (int i = 0; i < 3; i++) {
        int cnt = 0;
        for (int j = 0; j < 3; j++) {
            if (i == j) continue;
            if (all_equal(i, j)) break;
            if (good(i, j) >= good(j, i)) cnt++;
        }
        if (cnt == 2) {
            res = i;
            break;
        }
    }
    if (res == INT_MAX) {
        cout << "No dice\n";
    }
    else {
        cout << res + 1 << '\n';
    }
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    int t = 1;
    // cin >> t;
    while (t--) { 
        solve();
    }
    return 0;
}
