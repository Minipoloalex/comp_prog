#include <bits/stdc++.h>
using namespace std;

int dr[] = {0,0,1,-1};
int dc[] = {1,-1,0,0};

void solve() {
    int n;
    cin >> n;
    vector<string> g(n);
    for (auto &s: g) cin >> s;
    // if none is #, good
    // else if bfs yields everyone, good
    // else find one and build chains with it
    // check if good with bfs for every chain, i.g.
    int cnt = 0;
    pair<int,int> fst = {-1,-1};
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (g[i][j] == '#') {
                cnt++;
                fst = {i, j};
            }
        }
    }
    if (fst == pair<int,int>{-1,-1}) {
        cout << "YES\n";return;
    }
    for (int i = 0; i < n; i++) {
        int foll = 0;
        for (int j = 0; j < n; j++) {
            if (g[i][j] == '#') {
                foll++;
            }
            else foll = 0;
            if (foll >= 3) {
                cout << "NO\n";
                return;
            }
        }
    }
    for (int j = 0; j < n; j++) {
        int foll = 0;
        for (int i = 0; i < n; i++) {
            if (g[i][j] == '#') {
                foll++;
            }
            else foll = 0;
            if (foll >= 3) {
                cout << "NO\n";
                return;
            }
        }
    }
    auto inside = [&](int r, int c) {
        return r >= 0 && r < n && c >= 0 && c < n;
    };
    {
        vector<vector<int>> vis(n, vector<int>(n,0));
        queue<pair<int,int>> q;
        q.push(fst);
        vis[fst.first][fst.second] = 1;
        int cur_cnt = 1;
        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();
            for (int i = 0; i < 4; i++) {
                int nr = r + dr[i];
                int nc = c + dc[i];
                if (inside(nr, nc) && g[nr][nc] == '#' && !vis[nr][nc]) {
                    vis[nr][nc] = 1;
                    q.emplace(nr,nc);
                    cur_cnt++;
                }
            }
        }
        if (cur_cnt == cnt) {
            cout << "YES\n";
            return;
        }
    }

    int cur = 0;
    
    auto check = [&](int r, int c) {
        if (inside(r,c) && g[r][c] == '#') cur++;
    };
    cur = 0;
    {
        int r, c;
        r = fst.first, c = fst.second;
        check(r,c);
        while (inside(r, c)) {
            r++;
            check(r,c);
            c--;
            check(r,c);
        }
        r = fst.first, c = fst.second;
        while (inside(r, c)) {
            c++;
            check(r,c);
            r--;
            check(r,c);
        }
        if (cur == cnt) {
            cout << "YES\n";return;
        }
    }

    cur = 0;
    {
        int r, c;
        r = fst.first, c = fst.second;
        check(r,c);
        while (inside(r, c)) {
            r++;
            check(r,c);
            c++;
            check(r,c);
        }
        r = fst.first, c = fst.second;
        while (inside(r, c)) {
            c--;
            check(r,c);
            r--;
            check(r,c);
        }
        if (cur == cnt) {
            cout << "YES\n";return;
        }
    }

    cur = 0;
    {
        int r, c;
        r = fst.first, c = fst.second;
        check(r,c);
        while (inside(r, c)) {
            r--;
            check(r,c);
            c++;
            check(r,c);
        }
        r = fst.first, c = fst.second;
        while (inside(r, c)) {
            c--;
            check(r,c);
            r++;
            check(r,c);
        }
        if (cur == cnt) {
            cout << "YES\n";return;
        }
    }

    cur = 0;
    {
        int r, c;
        r = fst.first, c = fst.second;
        check(r,c);
        while (inside(r, c)) {
            r--;
            check(r,c);
            c--;
            check(r,c);
        }
        r = fst.first, c = fst.second;
        while (inside(r, c)) {
            c++;
            check(r,c);
            r++;
            check(r,c);
        }
        if (cur == cnt) {
            cout << "YES\n";return;
        }
    }
    cout << "NO\n";
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
