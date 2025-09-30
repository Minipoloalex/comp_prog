#include <bits/stdc++.h>
using namespace std;

void solve() {  
    int N = 21;

    int cnt = 0;
    for (int i = (1 << N) - 1; i > 0; i--) {
        vector<int> a(N);
        int last = 0;
        for (int j = 0; j < N; j++) {
            if (i & (1 << j)) {
                last = j;
                a[j] = 1;
            }
        }
        if (last >= 20) {
            cout << last << '\n';
            for (int k = 0; k <= last; k++) cout << a[k] << ' ';
            cout << '\n';
            cnt++;
        }

        if (cnt == 1000) break;
    }
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
