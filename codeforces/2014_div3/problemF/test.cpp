#include <bits/stdc++.h>
using namespace std;

int main() {
    int t = 1;
    int n = int(2e5);
    int c = int(1);
    cout << t << '\n';
    cout << n << " " << c << '\n';
    for (int i = 0; i < n; i++) {
        cout << int(1e9) << " ";
    }
    cout << '\n';
    for (int i = 1; i < n; i++) {
        cout << i << " " << i + 1 << '\n';
    }

    return 0;
}
