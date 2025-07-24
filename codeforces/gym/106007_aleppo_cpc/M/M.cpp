#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    if (n == 2) {
        cout << "1 2\n";
    }
    else if (popcount((unsigned int)n) == 1) {
        cout << "1 " << n << " 2";
        for (int i = 3; i < n; i++) {
            cout << " " << i;
        }
        cout << '\n';
    }
    
    else {
        vector<int> bits;
        for (int i = 0; i < 31; i++) {
            if ((1 << i) & n) {
                bits.push_back(i);
            }
        }
        int msb = bits.back();
        bits.pop_back();
        cout << n << " ";
        int cur = n;
        for (int b: bits) {
            cur -= (1 << b);
            for (int i = 0; i < (1 << b); i++) {
                cout << cur + i << " ";
            }
        }
        int save = n - (1 << msb);
        for (int i = 1; i < cur; i++) {
            if (i != save) {
                cout << i << " ";
            }
        }
        cout << save << '\n';
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
