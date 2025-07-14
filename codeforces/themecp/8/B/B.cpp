#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    if (n % 2 == 1) {
        vector<int> ans(n);
        if (n < 27) {
            cout << "-1\n";
        }
        else {
            cout << "1 2 3 4 5 6 7 8 9 1 2 3 4 5 6 7 8 9 10 10 11 11 12 13 13 1 12";
            int start = 13;
            for (int i = 1; i <= (n - 27) / 2; i++) {
                cout << " " << start + i << " " << start + i;
            }
            cout << '\n';
        }
    }
    else {
        for (int i = 1; i <= n / 2; i++) {
            cout << i << " " << i << " ";
        }
        cout << '\n';
    }
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
