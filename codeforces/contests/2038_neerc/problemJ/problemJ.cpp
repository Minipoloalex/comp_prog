#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    int waiting = 0;
    for (int i = 0; i < n; i++) {
        char c;
        int val;
        cin >> c >> val;
        if (c == 'B') {
            if (val > waiting) {
                cout << "YES\n";
            }
            else cout << "NO\n";
            waiting = max(0, waiting - val);
        }
        else {
            assert(c == 'P');
            waiting += val;
        }
    }
    return 0;
}
