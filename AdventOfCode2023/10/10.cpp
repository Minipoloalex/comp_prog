#include <bits/stdc++.h>
using namespace std;

// only part 1 implemented

typedef pair<int,int> ii;
ii WEST = {0, -1};
ii EAST = {0, 1};
ii NORTH = {-1, 0};
ii SOUTH = {1, 0};

map<char, array<ii, 2>> mp = {
    {'|', {NORTH, SOUTH}},
    {'-', {EAST, WEST}},
    {'L', {NORTH, EAST}},
    {'J', {NORTH, WEST}},
    {'7', {SOUTH, WEST}},
    {'F', {SOUTH, EAST}},
};
map<ii, ii> op = {
    {NORTH, SOUTH},
    {SOUTH, NORTH},
    {EAST, WEST},
    {WEST, EAST},
};


int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    vector<string> g;
    string s;
    while (getline(cin, s)) {
        if (s.empty()) break;
        g.push_back(s);
    }
    int n = (int) g.size();
    int m = (int) g.front().size();

    ii pos{-1, -1};
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (g[i][j] == 'S') {
                pos = {i, j};
                break;
            }
        }
    }
    assert(pos.first != -1 && pos.second != -1);
    auto inside = [&](int r, int c) {
        return r >= 0 && r < n && c >= 0 && c < m;
    };

    auto valid = [&](ii ori, char ncar) {
        if (ncar == '.') return false;
        ii opposite = op[ori];
        array<ii, 2> &dsnew = mp[ncar];
        for (int i = 0; i < 2; i++) {
            if (opposite == dsnew[i]) return true;
        }
        return false;
    };
    int ans = INT_MIN;
    auto try_start = [&](char ch) {
        vector<vector<int>> dist(n, vector<int>(m, -1));
        int mxdist = INT_MIN;
        bool possible, first = true;
        queue<ii> q;
        q.push(pos);
        dist[pos.first][pos.second] = 0;
        g[pos.first][pos.second] = ch;
        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();
            mxdist = max(mxdist, dist[r][c]);
            char at_pos = g[r][c];
            array<ii, 2> &ds = mp[at_pos];
            for (int i = 0; i < 2; i++) {
                auto [dr, dc] = ds[i];
                int nr = r + dr;
                int nc = c + dc;
                if (inside(nr, nc) && dist[nr][nc] == -1) {
                    char nchar = g[nr][nc];
                    if (valid(ds[i], nchar)) {
                        q.emplace(nr, nc);
                        dist[nr][nc] = dist[r][c] + 1;
                    }
                }
            }
            if (first) {
                if (q.size() == 2) {
                    possible = true;
                }
                else {
                    possible = false;
                    break;
                }
                first = false;
            }
        }
        if (possible) ans = max(ans, mxdist);
    };

    for (auto &[c, _]: mp) {
        try_start(c);
    }
    cout << ans << endl;
    return 0;
}
