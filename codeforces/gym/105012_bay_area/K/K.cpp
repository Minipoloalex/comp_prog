#include <bits/stdc++.h>
using namespace std;

int UP = 0;
int RIGHT = 1;
int DOWN = 2;
int LEFT = 3;

int nxt(int dir) {
    return (dir + 1) % 4;
}
pair<int,int> diff[] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
pair<int,int> movement(int dir) {
    return diff[dir];
}

void solve() {
    int n, m;
    cin >> n >> m;
    using T = array<int,3>;
    vector<T> pos(n);

    // no need to sort
    vector<T> people(n);
    for (auto &[x, y, t]: people) cin >> x >> y >> t;

    map<int,int> xs, ys;
    int curpersonidx = 0;
    for (int j = 0; j < m; j++) {
        while (curpersonidx < n && people[curpersonidx][2] == j) {
            auto &[x, y, t] = people[curpersonidx];
            xs[x]++;
            ys[y]++;
            pos[curpersonidx] = {x, y, UP};
            curpersonidx++;
        }
        map<int,int> newxs, newys;
        for (int i = 0; i < curpersonidx; i++) {
            auto &[x, y, dir] = pos[i];
            if (dir == UP || dir == DOWN) {
                int cnt = ys[y];
                if (cnt % 2 == 0) {
                    dir = nxt(dir);
                }
                auto [dx, dy] = movement(dir);
                x += dx;
                y += dy;
            }
            else {
                assert(dir == LEFT || dir == RIGHT);
                int cnt = xs[x];
                if (cnt % 2 == 0) {
                    dir = nxt(dir);
                }
                auto [dx, dy] = movement(dir);
                x += dx;
                y += dy;
            }
            newxs[x]++;
            newys[y]++;
        }
        ys.swap(newys);
        xs.swap(newxs);
    }
    for (int i = 0; i < n; i++) {
        auto &[x, y, dir] = pos[i];
        cout << x << " " << y << '\n';
    }
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
