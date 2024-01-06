#include <bits/stdc++.h>
using namespace std;

#define VISITED 2
typedef long long int ll;
typedef vector<ll> vll;

int mx[1000][1000];


ll id_0;
ll id_1;
vector<vll> flood_ids;

int r, c;

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

bool in_bounds(int ri, int ci) {
    return ri >= 0 && ci >= 0 && ri < r && ci < c;
}

void dfs(int ri, int ci, int val, int id) {
    flood_ids[ri][ci] = id;
    mx[ri][ci] = VISITED;
    // cout << "Set row " << ri << ", ci " << ci << " to visited" << endl;
    for (int i = 0; i < 4; i++) {
        int y = ri + dy[i];
        int x = ci + dx[i];
        // cout << "Trying: (" << y << ", " << x << ")" << endl;
        if (in_bounds(y, x) && mx[y][x] == val) {
            // if visited, does not call dfs(y, x, ...)
            // cout << "Another visit" << endl;
            dfs(y, x, val, id);
        }
    }
}

int main() {
    cin >> r >> c;
    char ch;
    for (int ri = 0; ri < r; ri++) {
        for (int ci = 0; ci < c; ci++) {
            cin >> ch;
            mx[ri][ci] = ch - '0';
        }
    }
    
    id_0 = 0;
    id_1 = 0;
    flood_ids.assign(r, vll(c));
    for (int ri = 0; ri < r; ri++) {
        for (int ci = 0; ci < c; ci++) {
            // cout << mx[ri][ci] << endl;
            if (mx[ri][ci] == VISITED) continue;
            if (mx[ri][ci] == 0) {
                id_0--;
                dfs(ri, ci, 0, id_0);
            }
            else {
                id_1++;
                dfs(ri, ci, 1, id_1);
            }
        }
    }

    int n; cin >> n;
    for (int ni = 0; ni < n; ni++) {
        int r1, r2, c1, c2;
        cin >> r1 >> c1 >> r2 >> c2; // [1, r] [1, c]
        r1--; c1--; r2--; c2--;
        if (flood_ids[r1][c1] != flood_ids[r2][c2]) {
            cout << "neither" << endl;
        }
        else if (flood_ids[r1][c1] < 0 && flood_ids[r1][c1] == flood_ids[r2][c2]) {
            cout << "binary" << endl;
        }
        else if (flood_ids[r1][c1] > 0 && flood_ids[r1][c1] == flood_ids[r2][c2]) {
            cout << "decimal" << endl;
        }
    }
    // for (int ri = 0; ri < r; ri++) {
    //     for (int ci = 0; ci < c; ci++) {
    //         cout << flood_ids[ri][ci] << " ";
    //     }
    //     cout << endl;
    // }
    return 0;
}
