#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> ii;

int w, h;
int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};

ii board[100][100];

// could remove size from the tuples and use board[r][c].first
struct army_cmp {
    bool operator()(const tuple<int,int,int> &a, const tuple<int,int,int> &b) const {
        const auto &[size1, r1, c1] = a;
        const auto &[size2, r2, c2] = b;
        return size1 > size2 || (size1 == size2 && r1 < r2) || (size1 == size2 && r1 == r2 && c1 < c2);
    }
};

bool is_valid(int x, int y) {
    return x >= 0 && y >= 0 && x < w && y < h;
}

int main() {
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    set<tuple<int,int,int>, army_cmp> pq; // greater first, then smaller second and smaller third
    
    cin >> w >> h;
    int currId = 0;
    for (int r = 0; r < h; r++) {
        for (int c = 0; c < w; c++) {
            int s;
            cin >> s;
            board[r][c] = make_pair(s, currId++);
            pq.emplace(s, r, c);
        }
    }
    while (pq.size() > 1) {
        auto &[size, r, c] = *pq.begin(); pq.erase(pq.begin());
        int id = board[r][c].second;
        // cout << "(" << c << "," << r << ") " << size << endl;
        int weakest = INT_MAX;
        int yWeak = -1;
        int xWeak = -1;
        for (int i = 0; i < 4; i++) {
            int x = c + dx[i];
            int y = r + dy[i];
            if (is_valid(x, y) && board[y][x].first != 0) {
                if (board[y][x].first < weakest ||
                (board[y][x].first == weakest && y < yWeak) ||
                (board[y][x].first == weakest && y == yWeak && x < xWeak)) {
                    yWeak = y;
                    xWeak = x;
                    weakest = board[y][x].first;
                }
            }
        }
        // cout << "(" << xWeak << ", " << yWeak << ") - " << weakest << endl;

        if (yWeak == -1) {
            board[r][c].first--;
            if (board[r][c].first > 0) pq.emplace(board[r][c].first, r, c);
        }
        else {
            pq.erase(pq.find({weakest, yWeak, xWeak}));
            
            board[r][c].first = 0;
            int new_size = size - weakest;
            board[yWeak][xWeak] = {new_size, id};
            tuple<int, int, int> new_army = {new_size, yWeak, xWeak};
            if (new_size > 0) {
                pq.insert(new_army);
            }
        }
    }
    if (pq.empty()) {
        cout << "none wins" << endl;
    }
    else {
        // pq.size() == 1
        auto &[size, r, c] = *pq.begin();
        int id = board[r][c].second;
        int y = id / w;
        int x = id % w;
        cout << y << " " << x << " " << size << endl;
    }


    return 0;
}

// only tested for 2 inputs
