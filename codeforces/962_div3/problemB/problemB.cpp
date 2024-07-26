#include <bits/stdc++.h>
using namespace std;

char mat[1010][1010];
char nmat[1010][1010];

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        for (int r = 0; r < n; r++) {
            for (int c = 0; c < n; c++) {
                cin >> mat[r][c];
            }
        }
        int nsize = n / k;

        for (int r = 0; r < nsize; r++) {
            for (int c = 0; c < nsize; c++) {
                nmat[r][c] = mat[r * k][c * k];
                cout << nmat[r][c];
            }
            cout << '\n';
        }
    }
    return 0;
}