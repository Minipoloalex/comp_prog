#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        string a;
        cin >> a;
        int n = (int) a.size();

        if (n == 3) {
            if (a[0] == '1' && a[1] == '0' && a[2] >= '2') {
                cout << "YES";
            }
            else cout << "NO";
        }
        else if (n >= 4) {
            if (a[0] == '1' && a[1] == '0') {
                int number = 0;
                for (int i = 2; i < n; i++) {
                    number *= 10;
                    number += a[i] - '0';
                }
                if (number >= 2 && a[2] != '0') cout << "YES";
                else cout << "NO";
            }
            else cout << "NO";
        }
        else cout << "NO";

        cout << '\n';
    }    
    return 0;
}
