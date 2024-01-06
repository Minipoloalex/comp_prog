#include <bits/stdc++.h>
using namespace std;

#define HOUSE -2
#define INVALID -1
#define EMPTY 0
#define VISITED -3

typedef vector<int> vi;
typedef pair<int, int> ii;

vector<vi> board;
vector<vi> board_ids;

int total_count = 0;
bool inside(int x, int y) {
    return y >= 0 && y < (int) board.size() && x >= 0 && x < (int) board.size();
}
int main() {
    int r, k;   // r [1, 50] k [1, R^3 - (R-1)^3]
    cin >> r >> k;
    int size = 2 * r - 1;
    board = vector<vi>(size, vi(size, INVALID));
    board_ids = vector<vi>(size, vi(size, INVALID));
    // uint total = (uint) pow(r, 3) - (uint) pow(r - 1, 3);
    uint val = 1;
    for (int row = 0; row < size; row++) {
        int width = size - abs(r - (row + 1));
        // cout << "row " << row << ", width " << width << endl; 
        int start = row < r ? 0 : row + 1 - r;
        for (int col = start; col < start + width; col++) {
            board[row][col] = val++;
            board_ids[row][col] = EMPTY;
        }
    }

    queue<ii> q;
    for (int i = 0; i < k; i++) {
        int house; cin >> house;
        bool done = false;
        for (int row = 0; row < (int) board.size() && !done; row++) {
            int width = size - abs(r - (row + 1));
            int start = row < r ? 0 : row + 1 - r;
            
            for (int col = start; col < start + width && !done; col++) {
                if (board[row][col] == house) {
                    board_ids[row][col] = HOUSE;
                    done = true;
                }
            }
        }
    }
    // careful about repeating positions in the queue
    for (int i = -1; i < (int) board.size() + 1; i++) {
        q.emplace(i, -1);   // (-1, -1) -> (n, -1)
        q.emplace(i, (int) board.size());   // (-1, n) -> (n, n)
    }
    for (int i = 0; i < (int) board.size(); i++) {
        q.emplace(-1, i);   // (-1, 0) -> (-1, n - 1)
        q.emplace((int) board.size(), i);   // (n, 0) -> (n, n - 1)
    }
    // for (int i = 0; i < (int) board.size(); i++) {
    //     for (int j = 0; j < (int) board[0].size(); j++) {
    //         cout << board[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    // cout << endl;
    // for (int i = 0; i < (int) board.size(); i++) {
    //     for (int j = 0; j < (int) board[0].size(); j++) {
    //         cout << board_ids[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    // cout << endl;
    int dx[] = {1, 0, -1, 0, -1, 1};
    int dy[] = {0, 1, 0, -1, -1, 1};
    
    while (!q.empty()) {
        ii pos = q.front(); q.pop();
        for (int i = 0; i < 6; i++) {
            int x = pos.first + dx[i];
            int y = pos.second + dy[i];
            bool is_inside = inside(x, y);
            if (is_inside && board_ids.at(y).at(x) == HOUSE) {
                // cout << "(" << pos.first << ", " << pos.second << ") -> " << "(" << x << ", " << y << "); ";
                total_count++;
            }
            else if (is_inside && board_ids[y][x] != VISITED) {
                q.emplace(x, y);
                board_ids[y][x] = VISITED;
            }
        }
    }
    // cout << endl;
    cout << total_count << endl;
    return 0;
}
