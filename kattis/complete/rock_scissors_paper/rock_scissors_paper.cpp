#include <bits/stdc++.h>
using namespace std;

typedef vector<char> vc;

vector<vc> grid_before;
vector<vc> grid_after;

bool wins(char possible_winner, char adj) {
    if (possible_winner == 'S') {
        return adj == 'P';
    }
    if (possible_winner == 'R') {
        return adj == 'S';
    }
    return possible_winner == 'P' && adj == 'R';
}

int main() {
    int t; cin >> t;
    while (t--) {
        // r c n positive ints <= 100
        int r, c, n;
        cin >> r >> c >> n;
        grid_before.assign(r, vc(c));

        for (int ri = 0; ri < r; ri++) {
            for (int ci = 0; ci < c; ci++) {
                cin >> grid_before[ri][ci];
            }
        }
        grid_after = grid_before;
        int dx[] = {0, 1, 0, -1};
        int dy[] = {1, 0, -1, 0};
        
        for (int ni = 0; ni < n; ni++) {
            bool has_updates = false;
            for (int ri = 0; ri < r; ri++) {
                for (int ci = 0; ci < c; ci++) {
                    char in_pos = grid_before[ri][ci];
                    grid_after[ri][ci] = in_pos;    // unnecessary since the arrays are copies
                    for (int i = 0; i < 4; i++) {
                        int x = ci + dx[i];
                        int y = ri + dy[i];
                        if (y < 0 || x < 0 || x >= c || y >= r) continue;
                        char adj = grid_before[y][x];
                        if (wins(adj, in_pos)) {
                            grid_after[ri][ci] = adj;
                            has_updates = true;
                            break;
                        }
                    }
                }
            }
            if (!has_updates) break;
            grid_before = grid_after;
        }
        for (int ri = 0; ri < r; ri++) {
            for (int ci = 0; ci < c; ci++) {
                cout << grid_after[ri][ci];
            }
            cout << endl;
        }
        cout << endl;
    }
    return 0;
}
