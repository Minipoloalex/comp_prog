#include <bits/stdc++.h>
using namespace std;

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

bool ask(int x, int y) {
    cout << x << " " << y << endl;
    string ret;
    cin >> ret;
    return ret == "hit";
}

void solve() {
    int n, k;
    cin >> n >> k;
    vector<pair<int,int>> locs;
    auto inside = [&](int x, int y) {
        return x >= 1 && x <= n && y >= 1 && y <= n;
    };
    for (int i = 5; i <= 2*n + 5; i += 5) {
        for (int j = 1; j <= n; j++) {
            int x = i - j + 1;
            int y = j;
            if (inside(x, y) && ask(x, y)) locs.emplace_back(x, y);
        }
    }
    for (auto &[x, y]: locs) {
        for (int i = 1; i <= 4; i++) {
            for (int j = 0; j < 4; j++) {
                int nx = x + i * dx[j];
                int ny = y + i * dy[j];
                if (inside(nx, ny)) ask(nx, ny);
            }
        }
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
