#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        int n, s, m;
        cin >> n >> s >> m;
        int prev = 0;
        bool yes = false;
        for (int i = 0; i < n; i++) {
            int li, ri;
            cin >> li >> ri;
            if (li - prev >= s) yes = true;
            prev = ri;
        }
        if (m - prev >= s) yes = true;
        if (yes) cout << "YES\n";
        else cout << "NO\n";
    }    
    return 0;
}
