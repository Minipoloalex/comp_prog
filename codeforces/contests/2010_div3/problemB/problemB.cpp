#include <bits/stdc++.h>
using namespace std;

int main() {
    int a, b;
    cin >> a >> b;
    int mn = min(a, b), mx = max(a, b);
    for (int i = 1; i <= 3; i++) {
        if (i != mn && i != mx) {
            cout << i << '\n';
        }
    }
    return 0;
}
