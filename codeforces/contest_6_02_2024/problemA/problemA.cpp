#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ul;
typedef long long ll;
typedef vector<int> vi;


int main() {
    cin.tie(NULL)->ios::sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        string line;
        cin >> line;
        int a[11] = {0};
        for (int i = 0; i < n; i++) {
            char c = line[i];
            if (c == 'B') {
                if (i == 0) {
                    a[i] = 1;
                }
                else {
                    a[i] = a[i - 1] + 1;
                }
            }
            else {
                a[i] = i == 0 ? 0 : a[i - 1];
            }
        }
        bool first = true;
        int last_value = -1;
        int f = 0, l = 0;

        for (int i = 0; i < n; i++) {
            if (first && a[i] == 1) {
                f = i;
                first = false;
            }
            if (a[i] != last_value) {
                l = i;
                last_value = a[i];
            }
        }
        cout << l - f + 1 << '\n';
    }
    return 0;
}
