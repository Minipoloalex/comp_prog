#include <bits/stdc++.h>
using namespace std;

const int MAX_N = int(2e5);
bitset<MAX_N + 10> bs;

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        
        bs.reset();
        bool yes = true;

        int ai;
        cin >> ai;
        bs.set(ai);
        for (int i = 1; i < n; i++) {
            cin >> ai;
            if (!bs[ai - 1] && !bs[ai + 1]) {
                yes = false;
            }
            bs.set(ai);
        }
        if (yes) cout << "YES\n";
        else cout << "NO\n";
    }
    return 0;
}
