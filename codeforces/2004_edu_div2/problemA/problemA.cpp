#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];   // n [2, 40]
        if (a.size() == 2) {
            if (abs(a[1] - a[0]) <= 1) {
                cout << "NO\n";
            }
            else cout << "YES\n";
        }
        else cout << "NO\n";
    }
    return 0;
}
