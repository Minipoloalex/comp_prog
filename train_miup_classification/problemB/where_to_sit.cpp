#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> ii;

int m, n;
int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};

// int y = id / w;  // id [0, n - 1]
// int x = id % w;

int calc_man_dist(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

int main() {
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    cin >> m >> n;
    int k;
    cin >> k;
    vector<ii> friends;
    for (int i = 0; i < k; i++) {
        int f;
        cin >> f;
        f--;
        int y = f/n;
        int x = f % n;
        friends.emplace_back(y, x);
    }
    ii best_pos = make_pair(-1, -1);
    bool first = true;
    for (int r = 0; r < m; r++) {
        for (int c = 0; c < n; c++) {
            // x1, y1, x2, y2
            int dist = calc_man_dist(friends.front().second, friends.front().first, c, r);
            bool possible = true;
            for (int f = 1; f < k && possible; f++) {
                ii fr = friends[f];
                if (calc_man_dist(fr.second, fr.first, c, r) != dist) {
                    possible = false;
                }
            }
            if (possible) {
                if (first) {
                    first = false;
                    best_pos = make_pair(r, c);
                }
                else if (r < best_pos.first || (r == best_pos.first && c < best_pos.second)) {  // lowest number is smaller r, then smaller c
                    best_pos = make_pair(r, c);
                }
            }
        }
    }
    if (best_pos.first == -1) {
        cout << -1 << endl;
    }
    else {
        // row * n_cols + col + 1
        cout << best_pos.first * n + best_pos.second + 1 << endl;
    }
    return 0;
}
