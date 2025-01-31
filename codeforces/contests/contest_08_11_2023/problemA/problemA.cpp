#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int a[3];
        for (int i = 0; i < 3; i++) {
            cin >> a[i];
        }
        bool finished = false;
        for (int i = 0; i < 3 && !finished; i++) {
            for (int j = i + 1; j < 3 && !finished; j++) {
                if (a[i] + a[j] >= 10) {
                    cout << "YES" << endl;
                    finished = true;
                }
            }
        }
        if (!finished) {
            cout << "NO" << endl;
        }
    }
    return 0;
}
