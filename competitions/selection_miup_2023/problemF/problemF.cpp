#include <bits/stdc++.h>
using namespace std;

int r, c;
int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};
typedef pair<int, int> ii;
typedef vector<int> vc;
typedef vector<vc> vvc;
vvc start_board(201, vc(201, 0));

void bfs_board(ii hero, vvc &board) {
    queue<ii> q;
    board.at(hero.first).at(hero.second) = 0;
    
    q.push(hero);
    while (!q.empty()) {
        ii h = q.front(); q.pop();
        int time = board.at(h.first).at(h.second);
        
        for (int i = 0; i < 4; i++) {
            int x = h.second + dx[i];
            int y = h.first + dy[i];
            if (x >= 0 && y >= 0 && x < c && y < r && board.at(y).at(x) == -1) {
                q.emplace(y, x);
                board.at(y).at(x) = time + 1;
            }
        }
    }
}
int main() {
    cin.tie(0); ios::sync_with_stdio(0);
    cin >> r >> c;
    vector<ii> heroes;
    vector<vvc> boards;
    for (int row = 0; row < r; row++) {
        for (int col = 0; col < c; col++) {
            char ch;
            cin >> ch;
            if (ch == '.') {
                start_board.at(row).at(col) = -1;
            }
            else if (ch == '#') {
                start_board.at(row).at(col) = -2;
            }
            else {
                start_board.at(row).at(col) = -1;
                heroes.emplace_back(row, col);
            }
        }
    }
    for (auto &_: heroes) {
        // cout << h.first << " " << h.second << endl;
        vvc hero_board(r, vc(c, 0));
        for (int row = 0; row < r; row++) {
            for (int col = 0; col < c; col++) {
                hero_board.at(row).at(col) = start_board.at(row).at(col);
            }
        }
        boards.push_back(hero_board);
    }
    // cout << "Finished copying to heroes" << endl;
    for (int i = 0; i < (int) heroes.size(); i++) {
        ii hero = heroes.at(i);
        bfs_board(hero, boards.at(i));
    }
    // cout << "Finished bfs through heroes' boards" << endl;
    int min_time = INT_MAX;
    for (int row = 0; row < r; row++) {
        for (int col = 0; col < c; col++) {
            bool valid = true;
            int max_h = -1;
            for (int i = 0; i < (int) boards.size(); i++) {
                int time = boards.at(i).at(row).at(col);
                if (time < 0) {
                    valid = false;
                }
                max_h = max(time, max_h);
                // cout << time << " ";
            }
            if (valid) min_time = min(max_h, min_time);
            // cout << " - " << min_time << endl;
        }
    }
    if (min_time == INT_MAX) {
        cout << "NOT POSSIBLE" << endl;
    }
    else {
        cout << min_time << endl;
    }
    return 0;
}
