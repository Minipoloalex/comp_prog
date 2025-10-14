#include <bits/stdc++.h>
using namespace std;

void solve() {
    string s;
    cin >> s;

    int cur = 0;

    array<int, 2> games{}, score{};

    for (char c : s) {
        if (c == 'S') {
            score[cur]++;
        } else if (c == 'R') {
            score[cur = !cur]++;
        }

        bool game = score[cur] == 10 || (score[cur] >= 5 && score[cur] - score[!cur] >= 2);
        if (game) {
            games[cur]++;
            score[cur] = score[!cur] = 0;
        }

        if (c == 'Q') {
            if (games[0] == 2 || games[1] == 2) {
                cout << games[0];
                if (cur == 0) cout << " (winner)";
                cout << " - " << games[1];
                if (cur == 1) cout << " (winner)";
                cout << '\n';
            } else {
                cout << games[0] << " (" << score[0];
                if (cur == 0) cout << "*";
                cout << ") - " << games[1] << " (" << score[1];
                if (cur == 1) cout << "*";
                cout << ")\n";
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
