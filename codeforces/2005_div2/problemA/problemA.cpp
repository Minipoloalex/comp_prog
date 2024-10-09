#include <bits/stdc++.h>
using namespace std;

int main() {
    char ch[5] = {'a', 'e', 'i', 'o', 'u'};
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        int rst = n % 5;
        for (int c = 0; c < 5; c++) {
            for (int cnt = 0; cnt < n / 5; cnt++) {
                cout << ch[c];
            }
            if (rst > 0) {
                cout << ch[c];
                rst--;
            }
        }
        cout << '\n';
    }
    return 0;
}
