#include <bits/stdc++.h>
using namespace std;

int wins(int a1, int a2, int b1, int b2) {
    return (a1 > b1 && a2 > b2) || (a1 == b1 && a2 > b2) || (a1 > b1 && a2 == b2);
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int a1, a2, b1, b2;
        cin >> a1 >> a2 >> b1 >> b2;
        int ans = wins(a1, a2, b1, b2) + wins(a1, a2, b2, b1) + wins(a2, a1, b1, b2) + wins(a2, a1, b2, b1);
        cout << ans << '\n';
    }    
    return 0;
}
