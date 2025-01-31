#include <bits/stdc++.h>
using namespace std;

char m[8][8];

typedef pair<int, int> ii;

int main() {
    int t;
    cin >> t;
    while (t--) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                cin >> m[i][j];
            }
        }
        ii first;
        bool finished = false;
        for (int i = 0; i < 8 && !finished; i++) {
            for (int j = 0; j < 8 && !finished; j++) {
                if (m[i][j] != '.') {
                    first = make_pair(i, j);
                    finished = true;
                }
            }
        }
        int col = first.second;
        string res;
        for (int row = first.first; row < 8; row++) {
            if (m[row][col] == '.') {
                break;
            }
            else {
                res += m[row][col];
            }
        }
        cout << res << endl;
    }
    return 0;
}
