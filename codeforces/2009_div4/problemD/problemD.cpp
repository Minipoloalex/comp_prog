#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> ii;

const int MAX_N = 2e5 + 10;
bool mat[MAX_N][2];

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<ii> pts(n);
        memset(mat, 0, sizeof(mat));

        for (int i = 0; i < n; i++) {
            int xi, yi;
            cin >> xi >> yi;
            pts[i] = make_pair(xi, yi);
        }
        sort(pts.begin(), pts.end());

        int64_t ans = 0;
        int count_perp = 0;
        for (int i = 0; i < n; i++) {
            auto &[xi, yi] = pts[i];
            if (xi - 1 >= 0 && mat[xi - 1][1 - yi] && xi - 2 >= 0 && mat[xi - 2][yi]) {
                ans++;
                // cout << "Counting weird triangle: " << i << endl;
            }

            ans += count_perp;
            if (mat[xi][1 - yi]) {
                // cout << "Found a perpendicular: " << i << endl;
                ans += i - 1;
                count_perp++;
            }
            // cout << i << " " << ans << endl;

            mat[xi][yi] = 1;
        }
        cout << ans << '\n';
    }
    return 0;
}
