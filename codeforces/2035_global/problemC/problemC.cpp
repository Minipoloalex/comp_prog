#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    auto print = [](int n, vector<int> &selected) {
        for (int i = 1; i <= n; i++) {
            bool to_print = true;
            for (int s: selected) {
                if (i == s) {
                    to_print = false;
                    break;
                }
            }
            if (to_print) cout << i << " ";
        }
        for (int s: selected) {
            cout << s << " ";
        }
        cout << '\n';
    };
    while (t--) {
        int n;
        cin >> n;
        
        if (n % 2 == 1) {
            vector<int> selected = {1, 3, n - 1, n};
            cout << n << '\n';
            print(n, selected);
        }
        else {
            int n_size = 0, ncp = n;
            while (ncp) {
                ncp >>= 1;
                n_size++;
            }
            int x = ((1 << n_size) - 1) ^ n;

            int x_minus_one = x - 1;
            if (x_minus_one == 0) x_minus_one = 2;

            int first = 1;
            if (x == 1) first = 5;

            int second = 3;
            if (x == 3) second = 5;

            vector<int> selected = {first, second, x_minus_one, x, n};
            cout << (1 << n_size) - 1 << '\n';
            print(n, selected);
        }
    }
    return 0;
}
