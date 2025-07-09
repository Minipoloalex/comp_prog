#include <bits/stdc++.h>
using namespace std;

void solve() {
    string king, rook, tg;
    cin >> king >> rook >> tg;

    bool can = false;

    auto in_range = [](const string& p, int r, int c) {
        return abs(p[0] - r) <= 1 && abs(p[1] - c) <= 1;
    };

    for (char c = rook[0]; c <= 'h'; c++) {
        if (c == king[0] && rook[1] == king[1]) break;
        if (in_range(king, c, rook[1])) continue;
        if (in_range(tg, c, rook[1])) can = true;
    }

    for (char c = rook[0]; c >= 'a'; c--) {
        if (c == king[0] && rook[1] == king[1]) break;
        if (in_range(king, c, rook[1])) continue;
        if (in_range(tg, c, rook[1])) can = true;
    }

    for (char r = rook[1]; r <= '8'; r++) {
        if (r == king[1] && rook[0] == king[0]) break;
        if (in_range(king, rook[0], r)) continue;
        if (in_range(tg, rook[0], r)) can = true;
    }

    for (char r = rook[1]; r >= '1'; r--) {
        if (r == king[1] && rook[0] == king[0]) break;
        if (in_range(king, rook[0], r)) continue;
        if (in_range(tg, rook[0], r)) can = true;
    }

    cout << (can ? "YES" : "NO") << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
